#include "StepperMotor.hpp"
#include <Arduino.h>

StepperMotor::StepperMotor(int stepperPin, int directionPin)
    : stepperPin(stepperPin), directionPin(directionPin)
{
    pinMode(stepperPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    setSpeed(RPM);
}

void StepperMotor::setSpeed(float RPM)
{
    this->RPM = RPM;
    if (RPM == 0)
    {
        usStepDelay = 0;
        return;
    }
    usStepDelay = 60000000 / (stepsPerRevolution * microstepsPerStep * abs(RPM));
    if (RPM < 0)
    {
        digitalWrite(directionPin, HIGH);
    }
    else
    {
        digitalWrite(directionPin, LOW);
    }
}

void StepperMotor::writePins(long usTime)
{
    if (enabled && usStepDelay != 0)
    {
        if ((usTime - lastStepTime) >= usStepDelay)
        {
            digitalWrite(stepperPin, HIGH);
            lastStepTime = usTime;
        }
    }
}

void StepperMotor::writeLow()
{
    digitalWrite(stepperPin, LOW);
}

void StepperMotor::enable()
{
    enabled = true;
}

void StepperMotor::disable()
{
    enabled = false;
}