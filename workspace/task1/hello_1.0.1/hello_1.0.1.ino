/**
* NAME: Ashwin K
* RNO: EE25B018
* DESC: LED blinks with a frequency of 18Hz (rno, can be any set frequency)
*/

uint8_t rno = 18;
double del;
uint8_t led = 6;

void setup()
{
  pinMode(led,OUTPUT);
  del = 500.0/rno;
}

void loop()
{
  digitalWrite(led, HIGH);
  delay(del); // Wait for one half cycle
  digitalWrite(led, LOW);
  delay(del); // Wait for one half cycle
}