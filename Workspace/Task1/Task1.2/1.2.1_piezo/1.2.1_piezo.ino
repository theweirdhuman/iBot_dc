/**
* TASK: 1.2.1
* NAME: Piezo Buzzer
* DESC: The buzzer produces a simple beeping pattern. (On-Off cycle in 2 seconds)
*/

uint8_t buzzPin = 8;

void setup()
{
  pinMode(buzzPin, OUTPUT);
}

void loop()
{
  tone(buzzPin, 2000);
  delay(1000);
  noTone(buzzPin);
  delay(1000);
}