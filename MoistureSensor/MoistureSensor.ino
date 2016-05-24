int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
 
void setup() {
   Serial.begin(9600);  
}
 
void loop() {
  // read the value from the moisture sensor:
  sensorValue = analogRead(sensorPin);  
  delay(1000);
  
  Serial.print("Moisture value: " );                       
  Serial.println(sensorValue);                   
}
