/** 
* NAME: Ashwin K
* RNO: EE25B018
* DESC: DTH11 is used to measure the temperature and humidity of the room
*/

#include <Adafruit_GFX.h>
#include <DHT.h>

uint8_t dataPin = A0;

DHT dht(dataPin, DHT11);

double humidity, temp;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(dataPin,INPUT);
  Serial.begin(9600);
  dht.begin();
  Serial.println("Temperature and Humidity readings:");
}

void loop()
{
  humidity = dht.readHumidity();
  temp = dht.readTemperature();

  if(isnan(humidity) || isnan(temp))
  {
    Serial.println("Reading Failed");
  }
  else
  {
    Serial.print("Humidity : ");
    Serial.print(humidity);
    Serial.print("%, Temperature : ");
    Serial.print(temp);
    Serial.println("°C");
  }

  delay(1000);
  
}