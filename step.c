#include "step.h"

void setup(int *periods)
{
    // Calculate the periods for each RPM value
    periods[0] = 1.0E6 / (rpm_1 * 200.0 / 60.0);
    periods[1] = 1.0E6 / (rpm_2 * 200.0 / 60.0);
    periods[2] = 1.0E6 / (rpm_3 * 200.0 / 60.0);
    periods[3] = 1.0E6 / (rpm_4 * 200.0 / 60.0);

    // Initialize GPIOs
    if (gpioInitialise() < 0)
    {
        fprintf(stderr, "pigpio initialization failed\n");
    }

    // Set GPIOs as oupu
    gpioSetMode(pin1, PI_OUTPUT); // Set GPIO18 as output.
    gpioSetMode(pin2, PI_OUTPUT); // Set GPIO18 as output.
    gpioSetMode(pin3, PI_OUTPUT); // Set GPIO18 as output.
    gpioSetMode(pin4, PI_OUTPUT); // Set GPIO18 as output.
}


