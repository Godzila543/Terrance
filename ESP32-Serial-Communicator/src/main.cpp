#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop()
{
  if (Serial.available())
  {
    String input = Serial.readStringUntil('\n');
    Serial.println(input);
  }
  // put your main code here, to run repeatedly:
}
