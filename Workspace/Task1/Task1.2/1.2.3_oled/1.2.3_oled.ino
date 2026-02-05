/**
* TASK: 1.2.3
* NAME: I2C OLED Display
* DESC: Display text and shapes on the OLED screen
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const uint8_t width = 128;
const uint8_t height = 64;
const uint8_t resetPin = -1;

Adafruit_SSD1306 display(width, height, &Wire, resetPin);


void setup()
{
  Serial.begin(9600);
  Serial.println("why");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { 
    Serial.println("SSD1306 Allocation Failed!");
  } 

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop()
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Hello world!");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Ashwin from iBot");
  display.setCursor(0,10);
  display.println("presents...");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.drawRect(10,5,108,54,SSD1306_WHITE);
  display.drawRect(20,15,42,30,SSD1306_WHITE);
  display.drawRect(72,15,42,30,SSD1306_WHITE);
  display.fillRect(50,35,12,10,SSD1306_WHITE);
  display.fillRect(102,35,12,10,SSD1306_WHITE);
  display.setCursor(66,48);
  display.println("U");
  display.display();
  delay(6000);
  display.clearDisplay();
  display.drawCircle(63,31,30,SSD1306_WHITE);
  display.setCursor(51,27);
  display.println("iBot");
  display.display();
  delay(6000);
}