#include <pigpio.h>

class StepperController
{
    float rpm;
    int previous_step;
    int period_us;
    int pin;
    int direction;

  public:
    void updateActivation(int32_t time);
    void deactivate();
    StepperController(int _pin = 27, float rpm = 60);
    void setRPM(float rpm);
  };
