#include <SPI.h>
#include <TempSensor.h>
int TempPin = A0;
float TempThres = 0.10;
TempSensor TS(TempPin,TempThres);

void setup() {
  TS.begin();
}

void loop() {
  TS.Sensor_to_Temp();
  Serial.print("Temp :");
  Serial.println(TS.Value());
  delay(1000);
}
