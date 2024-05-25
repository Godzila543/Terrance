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

  gpioInitialise();
  StepperController motors[4];
  motors[0] = StepperController(pin1, 15);
  motors[1] = StepperController(pin2, 30);
  motors[2] = StepperController(pin3, 0);
  motors[3] = StepperController(pin4, 0);

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


    // Control Code
    motors[0].setRPM(gamepad.triggers.left);
    motors[1].setRPM(gamepad.triggers.right);
    // Get current time
    uint32_t current_time = gpioTick();
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
