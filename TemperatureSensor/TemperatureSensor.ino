/* Grove - Temprature Sensor demo v1.0
*  This sensor detects the enviroment temprature,
*  Connect the signal of this sensor to A0, use the 
*  Serial monitor to get the result.
*  By: http://www.seeedstudio.com
*/
#include <math.h>
#include <Wire.h>
int a;
float t;
int B=4250;                  //B value of the thermistor
float resistance;

void setup()
{
    Serial.begin(9600);  
}

void loop()
{
    a = analogRead(A2);
    resistance = (float)(1023 - a) * 10000 / a;
    t = (float)(1 / (log(resistance / 10000) / 4250 + 1 / 298.15) - 273.15);
    delay(1000);
    Serial.print("Current temperature is ");
    Serial.println(t);
}
