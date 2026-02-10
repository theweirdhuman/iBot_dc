/** 
* TASK: 1.1.4
* NAME: Ultrasonic
* DESC: Read data from ultrasonic sensor and display the distance on the Serial monitor
*/

uint8_t trig = 2;
uint8_t echo = 8;


void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  Serial.println("Distance recorded:");
}

void loop()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  unsigned long time = pulseIn(echo,HIGH);
  double distance = (0.0343*time) / 2.0; //result in cm
  Serial.println(distance);

  delay(50);
}