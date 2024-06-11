#include <cstdio>
#include <pigpio.h>
#include <thread>
#include <csignal>
// #include <stdio.h>
// #include <unistd.h>
// #include <time.h>

#include "pins.hpp"
#include "StepperController.hpp"
#include "ControllerSubscriber.hpp"
#include "Ackermann.hpp"
// #include "listener.hpp"

volatile std::sig_atomic_t flag = 0;

void signal_handler(int _signal)
{
  flag = 1;
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  printf("hello world cpp_stepper_controller package\n");

  // Watch for interupt signal
  std::signal(SIGINT, signal_handler);

  AckermannSteering ackermann(200.0, 200.0, 50.0, 30.0);
  ackermann.setSteeringAngle(0);
  ackermann.setSpeed(0);

  gpioInitialise();
  uint32_t start_time = gpioTick();
  StepperController motors[4];
  motors[0] = StepperController(pin1, dirPin1);
  motors[1] = StepperController(pin2, dirPin2);
  motors[2] = StepperController(pin3, dirPin3);
  motors[3] = StepperController(pin4, dirPin4);

  // Setup ROS listener node
  rclcpp::init(argc, argv);

  auto controller_subscriber = std::make_shared<ControllerSubscriber>();

  // Spin the node in a thread to allow execution to continue
  std::thread listener_thread([&controller_subscriber]()
                              { rclcpp::spin(controller_subscriber); });

  while (!flag)
  {
    const Gamepad &gamepad = controller_subscriber->getGamepad();
    // test log to see if gamepad is being read
    // printf("left_stick.x: %d\n", gamepad.left_stick.x);

    // Ackermann Steering
    ackermann.setSteeringAngle(gamepad.left_stick.x / 5000.0);
    double speed = (gamepad.triggers.right - gamepad.triggers.left) / 255.0;
    speed = pow(abs(speed), 2.0) * (speed < 0 ? -1 : 1);
    speed *= 1000.0;
    ackermann.setSpeed();
    
    // Set RPMs
    RPMs rpms = ackermann.getRPMs();
    printf("FL: %f, FR: %f, RL: %f, RR: %f\n", rpms.frontLeft, rpms.frontRight, rpms.rearLeft, rpms.rearRight);
    motors[0].setRPM(rpms.frontLeft);
    motors[1].setRPM(rpms.frontRight);
    motors[2].setRPM(rpms.rearLeft);
    motors[3].setRPM(rpms.rearRight);

    // Get current time
    uint32_t current_time = gpioTick() - start_time;
    motors[0].updateActivation(current_time);
    motors[1].updateActivation(current_time);
    motors[2].updateActivation(current_time);
    motors[3].updateActivation(current_time);

    // Stay high for 1000 us
    gpioDelay(1000);

    // Unpulse
    motors[0].deactivate();
    motors[1].deactivate();
    motors[2].deactivate();
    motors[3].deactivate();

    // Stay low for 1000 us
    gpioDelay(1000);
  }

  rclcpp::shutdown();
  listener_thread.join();
  return 0;
}
