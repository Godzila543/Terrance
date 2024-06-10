#include <pigpio.h>

class StepperController
{
    float rpm;
    int previous_step;
    int period_us;
    float rpm;
    int pin;
    int dirPin;
    int direction;

  public:
    void updateActivation(int32_t time);
    void deactivate();
    StepperController(int _pin = 27, int _dirPin = 27);
    void setRPM(float rpm);
  };
