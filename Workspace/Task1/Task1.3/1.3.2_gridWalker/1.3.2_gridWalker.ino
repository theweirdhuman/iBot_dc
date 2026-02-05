/**
* TASK: 1.3.2
* NAME: OLED Grid Walker
* DESC: Using button inputs, the user can control the movement of an 8x8 pixel block
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const uint8_t width = 128;
const uint8_t height = 64;
const uint8_t resetPin = -1;

Adafruit_SSD1306 display(width, height, &Wire, resetPin);

uint8_t upPin = 3;
uint8_t downPin = 5;
uint8_t rightPin = 2;
uint8_t leftPin = 4;
int posX = 56;
int posY = 24;
uint8_t upBut = 1;
uint8_t downBut = 1;
uint8_t rightBut = 1;
uint8_t leftBut = 1;

void setup()
{
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { 
    Serial.println("SSD1306 Allocation Failed!");
  } 

  
  display.clearDisplay();
  display.fillRect(posX,posY,8,8,SSD1306_WHITE);
  display.display();

  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
}

void loop()
{
  uint8_t newUpBut = digitalRead(upPin);
  uint8_t newDownBut = digitalRead(downPin);
  uint8_t newRightBut = digitalRead(rightPin);
  uint8_t newLeftBut = digitalRead(leftPin);

  
  if(newUpBut == 0 && upBut == 1)
  { 
    
    posY-=8;

    if(posY<0)
      posY=56;

    display.clearDisplay();
    display.fillRect(posX,posY,8,8,SSD1306_WHITE);
    display.display();
  }

  if(newDownBut == 0 && downBut == 1)
  { 
    posY+=8;

    if(posY>63)
      posY=0;

    display.clearDisplay();
    display.fillRect(posX,posY,8,8,SSD1306_WHITE);
    display.display();
  }

  if(newRightBut == 0 && rightBut == 1)
  { 
    posX+=8;

    if(posX>127)
      posX=0;

    display.clearDisplay();
    display.fillRect(posX,posY,8,8,SSD1306_WHITE);
    display.display();
  }

  if(newLeftBut == 0 && leftBut == 1)
  { 
    posX -= 8;

    if(posX<0)
      posX=120;

    display.clearDisplay();
    display.fillRect(posX,posY,8,8,SSD1306_WHITE);
    display.display();
  }


  upBut = newUpBut;
  downBut = newDownBut;
  rightBut = newRightBut;
  leftBut = newLeftBut;

}