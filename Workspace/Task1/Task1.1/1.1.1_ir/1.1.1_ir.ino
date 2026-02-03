/** 
* NAME: Ashwin K
* RNO: EE25B018
* DESC: Read data from IR sensor and display on Serial monitor
*/

uint8_t dataPin = A0;



void setup() {
  // put your setup code here, to run once:
  
  pinMode(dataPin,INPUT);
  Serial.begin(9600);
  Serial.println("IR module readings:");
}

void loop()
{
  int irRead = analogRead(dataPin);
  Serial.println(irRead);
  
}