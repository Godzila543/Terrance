#include "StepperController.hpp"
#include <pigpio.h>
// #include <cstdio>

StepperController::StepperController(int _pin, float rpm)
{
  pin = _pin;
  period_us = 1.0E6 / (rpm * 200.0 / 60.0);
  gpioSetMode(pin, PI_OUTPUT);
}

void StepperController::setRPM(float rpm)
{
  period_us = 1.0E6 / (rpm * 200.0 / 60.0);
}

void StepperController::updateActivation(uint32_t t)
{
  if (t - period_us > previous_step)
  {
    previous_step = t;
    gpioWrite(pin, 1);
  } 
}

void StepperController::deactivate()
{
  gpioWrite(pin, 0);
}
