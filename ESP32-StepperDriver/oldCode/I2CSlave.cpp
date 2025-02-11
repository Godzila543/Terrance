#include "I2CSlave.hpp"

StepperMotor *I2CSlave::motors = nullptr;
size_t I2CSlave::motorCount = 0;

I2CSlave::I2CSlave(uint8_t address, StepperMotor *motors, size_t motorCount)
{
    I2CSlave::motors = motors;
    I2CSlave::motorCount = motorCount;
    Wire.begin(address);
}

void I2CSlave::begin()
{
    Wire.onReceive(receiveEvent);
}

void I2CSlave::receiveEvent(int bytes)
{
    if (bytes < 5) // 1 byte for motor index + 4 bytes for float RPM
        return;

    uint8_t motorIndex = Wire.read();
    Serial.println(motorIndex);
    if (motorIndex >= motorCount)
        return;

    union
    {
        float rpm;
        uint8_t bytes[4];
    } rpmUnion;

    for (int i = 0; i < 4; i++)
    {
        rpmUnion.bytes[i] = Wire.read();
    }
    Serial.println(rpmUnion.rpm);

    motors[motorIndex].setSpeed(rpmUnion.rpm);
}