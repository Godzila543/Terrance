#include "StepperController.hpp"
#include <pigpio.h>
#include <cmath>
#include <cstdio>

StepperController::StepperController(int stepPin, int _dirPin)
{
  pin = stepPin;
  dirPin = _dirPin;
  period_us = 1.0E9;
  rpm = 0;
  previous_step = 0;
  gpioSetMode(pin, PI_OUTPUT);
  gpioSetMode(dirPin, PI_OUTPUT);
}

void StepperController::setRPM(float _rpm)
{
  rpm = _rpm;
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
  if (abs(rpm) < 0.01)
  {
    return;
  }
  // printf("%d\n", t - previous_step);
  if (t - previous_step > period_us)
  {
    // printf("step\n");
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
