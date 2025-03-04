#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Hello from ESP32!"); // prints Hello from ESP32!
  delay(1000);                         // wait for a second
  // put your main code here, to run repeatedly:
}
