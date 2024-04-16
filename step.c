#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define rpm_1 30
#define rpm_2 60
#define rpm_3 90
#define rpm_4 120

#define pin1 27
#define pin2 5
#define pin3 13
#define pin4 26

void setup(int *periods)
{
    // Calculate the periods for each RPM value
    periods[0] = 10.0E6 / (rpm_1 * 200.0 / 60.0);
    periods[1] = 10.0E6 / (rpm_2 * 200.0 / 60.0);
    periods[2] = 10.0E6 / (rpm_3 * 200.0 / 60.0);
    periods[3] = 10.0E6 / (rpm_4 * 200.0 / 60.0);

    // Set GPIOs as outputs
    gpioSetMode(pin1, PI_OUTPUT); // Set GPIO18 as output.
    gpioSetMode(pin2, PI_OUTPUT); // Set GPIO18 as output.
    gpioSetMode(pin3, PI_OUTPUT); // Set GPIO18 as output.
    gpioSetMode(pin4, PI_OUTPUT); // Set GPIO18 as output.
}

// test
void main(void)
{
    // Initialize GPIOs
    gpioInitialise();
    // Get periods
    int periods[4];
    setup(periods);

    // Initialize the previous step times
    uint32_t previous_step[4];
    for (unsigned char i = 0; i < 4; i++)
    {
        previous_step[i] = 0;
    }

    while (1)
    {
        // Get current time
        uint32_t current_time = gpioTick();

        // Motor 1
        if (current_time - previous_step[0] > periods[0])
        {
            // Step motor 1
            gpioWrite(pin1, 1);
            previous_step[0] = current_time;
        }

        // Motor 2
        if (current_time - previous_step[1] > periods[1])
        {
            // Step motor 2
            gpioWrite(pin2, 1);
            previous_step[1] = current_time;
        }

        // Motor 3
        if (current_time - previous_step[2] > periods[2])
        {
            // Step motor 3
            gpioWrite(pin3, 1);
            previous_step[2] = current_time;
        }

        // Motor 4
        if (current_time - previous_step[3] > periods[3])
        {
            // Step motor 4
            gpioWrite(pin4, 1);
            previous_step[3] = current_time;
        }

        // Stay high for 400 us
        gpioDelay(400);

        // Unpulse
        gpioWrite(pin1, 0);
        gpioWrite(pin2, 0);
        gpioWrite(pin3, 0);
        gpioWrite(pin4, 0);

        // Stay low for 400 us
        gpioDelay(400);
    }
}