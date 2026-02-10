/**
* TASK: 1.2.4
* NAME: Servo Motor Control
* DESC: The servo motor sweeps from 0◦ to 180◦ and back.
*/

#include <Servo.h>

Servo motor;

uint8_t servoPin = 6;

void setup()
{
  pinMode(servoPin, OUTPUT);
  motor.attach(servoPin;
}

void loop()
{
  for(int i = 0; i<=360; i++)
  {
    int deg = i>180?(360-i):i;
    motor.write(deg);
    delay(20);
  }
}