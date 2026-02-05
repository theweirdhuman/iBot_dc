/**
* TASK: 1.3.3
* NAME: Audio Visualizer  
* DESC: A sound's amplitude is displayed on the OLED in real time
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const uint8_t width = 128;
const uint8_t height = 64;
const uint8_t resetPin = -1;

Adafruit_SSD1306 display(width, height, &Wire, resetPin);

uint8_t soundDataPin = A0;

void setup()
{
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { 
    Serial.println("SSD1306 Allocation Failed!");
  } 

  
  display.clearDisplay();
  display.fillRect(0,31,128,2,SSD1306_WHITE);
  display.display();

  pinMode(A0,INPUT);
}

void loop()
{
  int height = analogRead(soundDataPin);
  Serial.println(height);
  height = map(height, 0, 1023, 0, 31);
  display.clearDisplay();
  display.fillRect(0,31,128,2,SSD1306_WHITE);
  display.fillRect(57,31-height,8,2*height,SSD1306_WHITE);
  display.display();
  delay(10);
}