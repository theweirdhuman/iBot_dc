/**
* TASK: 1.4
* NAME: Sonar
* DESC: Integrate a servo, ultrasonic module and OLED to create a primitive sonar.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

Servo servoObj;

const uint8_t width = 128;
const uint8_t height = 64;
const uint8_t resetPin = -1;
const uint8_t servoPin = 6;

uint8_t trig = 2;
uint8_t echo = 8;

Adafruit_SSD1306 display(width, height, &Wire, resetPin);

void drawSonar(double degRad);

double distance(); 

void setup()
{
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    Serial.println("SSD1306 Allocation Failed!");
  
  pinMode(servoPin, OUTPUT);
  servoObj.attach(servoPin);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo,INPUT);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop()
{
  for(int i = 0; i<=360; i++)
  {
    int deg = i>180?(360-i):i;
    double degRad = deg*3.14159/180;

    servoObj.write(deg);

    drawSonar(degRad);

    delay(20);

    double objRadius = map(distance()*100, 0, 40000, 0, 6300)/100; //maps to points within the oled
    int objX = 63+objRadius*cos(degRad);
    int objY = 63-objRadius*sin(degRad);
    display.drawPixel(objX, objY, SSD1306_WHITE);

    display.display();
  }
  
}

void drawSonar(double degRad)
{
  display.clearDisplay();
  //draw basic sonar elements, 3 = 0011 used for the bitmask, draws upper half of semicircle as our servo only goes from 0 to 180
  display.drawCircleHelper(63,63,63,3,SSD1306_WHITE);
  display.drawCircleHelper(63,63,42,3,SSD1306_WHITE);
  display.drawCircleHelper(63,63,21,3,SSD1306_WHITE);
  display.drawLine(63,63,63+63*cos(degRad),63-63*sin(degRad),SSD1306_WHITE); //sonar sweeping line
}

double distance()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  unsigned long time = pulseIn(echo,HIGH);
  double distance = (0.0343*time) / 2.0; //result in cm
  return distance;
}