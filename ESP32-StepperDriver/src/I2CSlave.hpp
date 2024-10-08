#ifndef I2CSLAVE_HPP
#define I2CSLAVE_HPP

#include <Wire.h>
#include "StepperMotor.hpp"

class I2CSlave
{
public:
    I2CSlave(uint8_t address, StepperMotor *motors, size_t motorCount);
    void begin();
    static void receiveEvent(int bytes);

private:
    static StepperMotor *motors;
    static size_t motorCount;
};

#endif // I2CSLAVE_HPP