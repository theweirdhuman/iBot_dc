/**
* TASK: 1.2.2
* NAME: 16 x 2 LCD Display
* DESC: Prints simple text messages on the LCD Display
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

void setup()
{
  lcd.begin(16, 2);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello World!");
  lcd.setCursor(0, 1);
  lcd.print("I'm Ashwin!");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello World!");
  lcd.setCursor(0, 1);
  lcd.print("iBot Club");
  delay(3000);
}