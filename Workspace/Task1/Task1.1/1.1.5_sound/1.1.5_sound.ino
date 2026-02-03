/** 
* NAME: Ashwin K
* RNO: EE25B018
* DESC: Read data from sound sensor and blink when a clap is heard
*/

uint8_t led = 10;
uint8_t soundReadingDig = 8;
uint8_t soundReadingAn = A0;


void setup()
{
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
  pinMode(soundReadingDig, INPUT);
  pinMode(soundReadingAn, INPUT);
  Serial.begin(9600);

  //unsigned long time = millis();
  // while(millis()-time<50000) //50 second itime for calibration
  // {
  //   Serial.println(analogRead(soundReadingAn));
  //   delay(20);
  // }
  
}

void loop()
{
  uint16_t  clap = analogRead(soundReadingAn);

  Serial.println(clap);

  
  
  if(clap>=1000)
  {
    digitalWrite(led,HIGH);
    delay(2000);
    digitalWrite(led,LOW);
    delay(50);
  }
  //delay(1);
}