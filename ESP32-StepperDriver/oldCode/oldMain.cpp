#include <Arduino.h>
#include "StepperMotor.hpp"
#include "I2CSlave.hpp"

StepperMotor motors[] = {
    StepperMotor(32, 33),
    StepperMotor(25, 26),
    StepperMotor(27, 14),
    StepperMotor(12, 13),
};

I2CSlave i2cSlave(0x08, motors, sizeof(motors) / sizeof(motors[0]));

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    for (auto &motor : motors)
    {
        motor.setSpeed(60);
    }
    i2cSlave.begin();
}

void loop()
{
    long usTime = micros();
    for (auto &motor : motors)
    {
        motor.setSpeed(100 * sin(usTime / 1060000.0));
    }

    for (auto &motor : motors)
    {
        motor.writePins(usTime);
    }
    delayMicroseconds(2);
    for (auto &motor : motors)
    {
        motor.writeLow();
    }
}
