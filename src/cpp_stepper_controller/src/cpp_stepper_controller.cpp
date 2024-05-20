#include <cstdio>
#include <pigpio.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <time.h>

#include "pins.hpp"
#include "StepperController.hpp"
#include "controller.hpp"
#include "listener.hpp"


int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  printf("hello world cpp_stepper_controller package\n");
  
  gpioInitialise();
  StepperController motors[4];
  motors[0] = StepperController(pin1, 15);
  motors[1] = StepperController(pin2, 30);
  motors[2] = StepperController(pin3, 45);
  motors[3] = StepperController(pin4, 60);

  auto controller = controller();

  // Setup ROS listener node
  listener = controllerSubscriber();

  while (1)
  {
    controller.update();

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
  return 0;
}
