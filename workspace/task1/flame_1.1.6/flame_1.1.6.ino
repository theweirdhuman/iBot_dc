/** 
* NAME: Ashwin K
* RNO: EE25B018
* DESC: Flame sensor reads data and prints it on the Serial monitor
*/

uint8_t dataPin = A0;



void setup() {
  // put your setup code here, to run once:
  
  pinMode(dataPin,INPUT);
  Serial.begin(9600);
  Serial.println("Flame sensor module readings:");
}

void loop()
{
  int flameRead = analogRead(dataPin);
  Serial.println(flameRead);
  
}