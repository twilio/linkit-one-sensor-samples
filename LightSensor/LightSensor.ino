/*
/* Grove - Light Sensor demo v1.0
* 
* signal wire to A0.
* By: http://www.seeedstudio.com
*/
//#include <math.h>

float Rsensor; //Resistance of sensor in K

void setup() {
  Serial.begin(9600);                //Start the Serial connection
}

void loop() {
  int sensorValue = analogRead(A0); 
  
  Rsensor=(float)(1023-sensorValue)*10/sensorValue;
  
  Serial.print("Analog value from sensor: ");
  Serial.println(sensorValue);
  
  Serial.print("Sensor resistance: ");
  Serial.println(Rsensor,DEC);
  
  delay(1000);
}
