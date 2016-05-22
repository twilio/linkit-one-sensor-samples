int loudnessValue;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  loudnessValue = analogRead(A0);
  Serial.println(loudnessValue);
  delay(200);
}
