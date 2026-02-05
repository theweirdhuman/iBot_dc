/**
* TASK: 1.3.1
* NAME: Laser Security System
* DESC: Laser points at an LDR, if the "tripwire" is tripped, a buzzer sounds. Output is displayed on the LCD.
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
uint8_t buzzPin = 8;
uint8_t ldrDataPin = 7;
uint8_t laserSignalPin = 9;

void setup()
{
  lcd.begin(16, 2);
  pinMode(buzzPin, OUTPUT);
  pinMode(ldrDataPin,INPUT);
  pinMode(laserSignalPin, OUTPUT);
  digitalWrite(laserSignalPin, HIGH);
}

void loop()
{
  uint8_t noLight = digitalRead(ldrDataPin);

  if(noLight)
  {
    tone(buzzPin, 2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Interference");
    lcd.setCursor(0, 1);
    lcd.print("Detected");
  }
  else
  {
    noTone(buzzPin);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Interference");
  }

  delay(50);

}