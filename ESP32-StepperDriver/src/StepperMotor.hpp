#include <Arduino.h>

class StepperMotor
{
private:
    static const int stepsPerRevolution = 200;
    static const int microstepsPerStep = 16;

    int stepperPin;
    int directionPin;

    float RPM = 0;
    int usStepDelay = 1;
    long lastStepTime = 0;
    bool enabled = true;

public:
    StepperMotor(int stepperPin, int directionPin);
    void setSpeed(float RPM);
    void writePins(long usTime);
    void writeLow();
    void enable();
    void disable();
};