#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>

// test
void main(void) {

    // Set mode
    gpioInitialise();
    gpioSetMode(27, PI_OUTPUT); // Set GPIO18 as output.

    // Step at 60 RPM
    for (int i = 0; i < 2000; i++) {

        // Step once
        gpioWrite(13, 1);

        // Wait for delay
        usleep(400);

        // Go low
        gpioWrite(13, 0);

        // Wait for delay
        usleep(400);

    }

    // gpioSetPWMfrequency(13, 200);
    // printf("Setting PWM");

}