/** 
* NAME: Ashwin K
* RNO: EE25B018
* DESC: Read data from LDR and display on Serial monitor
*/

uint8_t dataPin = A0;



void setup() {
  // put your setup code here, to run once:
  
  pinMode(dataPin,INPUT);
  Serial.begin(9600);
  Serial.println("LDR module readings:");
}

void loop()
{
  int ldrRead = analogRead(dataPin);
  Serial.println(ldrRead);
  
}