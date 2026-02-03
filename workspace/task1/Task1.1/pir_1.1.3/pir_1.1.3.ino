/** 
* NAME: Ashwin K
* RNO: EE25B018
* DESC: Read data from PIR sensor and display on Serial monitor
*/

uint8_t dataPin = 2;
uint8_t led = 8;


void setup() {
  // put your setup code here, to run once:
  
  pinMode(dataPin,INPUT);
  Serial.begin(9600);
  Serial.println("PIR module readings:");
}

void loop()
{
  int pirRead = digitalRead(dataPin);
  if(pirRead == 0)
  {
    Serial.println("Stationary");
    digitalWrite(led,LOW);
  }
  else
  {
    Serial.println("Motion Detected!");
    digitalWrite(led,HIGH);
  }
  
}