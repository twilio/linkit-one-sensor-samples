void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setting up touch sensor pin");

  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = digitalRead(2);
  
  if(sensorValue == 1)
  {
    Serial.println("Touch detected!");
  }
}
