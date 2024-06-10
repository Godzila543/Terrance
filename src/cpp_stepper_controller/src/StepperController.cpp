#include "StepperController.hpp"
#include <pigpio.h>
#include <cmath>
// #include <cstdio>

StepperController::StepperController(int stepPin, int _dirPin)
{
  pin = stepPin;
  dirPin = _dirPin;
  period_us = 1.0E9;
  gpioSetMode(pin, PI_OUTPUT);
  gpioSetMode(dirPin, PI_OUTPUT);
}

void StepperController::setRPM(float rpm)
{
  if (rpm < 0)
  {
    direction = -1;
  } else {
    direction = 1;
  }
  period_us = 1.0E6 / (abs(rpm) * 200.0 / 60.0);
}

void StepperController::updateActivation(int32_t t)
{
  if (t - period_us > previous_step)
  {
    previous_step = t;
    gpioWrite(pin, 1);
  }
  if (direction == 1)
  {
    gpioWrite(dirPin, 1);
  } else {
    gpioWrite(dirPin, 0);
  }
}

void StepperController::deactivate()
{
  gpioWrite(pin, 0);
}
