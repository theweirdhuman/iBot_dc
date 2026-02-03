/** 
* NAME: Ashwin K
* RNO: EE25B018
* DESC: Push button to toggle LED
*/

uint8_t pinPush = 2;
uint8_t pinLED = 8;
int buttonOld = 1;


void setup() {
  // put your setup code here, to run once:
  pinMode(pinPush, INPUT_PULLUP);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);

  
}

void loop()
{
  int state = digitalRead(pinLED);
  int buttonNew = digitalRead(pinPush);
  if(buttonOld == 1 && buttonNew == 0)
  {
    digitalWrite(pinLED, !(state));
    delay(50);
  }

  buttonOld = buttonNew;
  
}