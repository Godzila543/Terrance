
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

void setup(int *periods);
