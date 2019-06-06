int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorPin1 = A1;    // select the input pin for the potentiometer
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorPin2 = A2;    // select the input pin for the potentiometer
int sensorValue2 = 0;  // variable to store the value coming from the sensor

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
/** 
  sensorValue = analogRead(sensorPin);
 Serial.println(sensorValue);

*/
  sensorValue = analogRead(sensorPin);
   sensorValue1 = analogRead(sensorPin1);
      sensorValue2 = analogRead(sensorPin2);
   Serial.print(sensorValue);
   Serial.print(",");
 Serial.print(sensorValue1);
    Serial.print(",");
 Serial.println(sensorValue2);
  delay(10);
}
