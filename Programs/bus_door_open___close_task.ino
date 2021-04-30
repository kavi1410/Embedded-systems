const int sensorMin = 0;
const int sensorMax = 600;

void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);

Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly: 
  int sensorvalue = analogRead(2);
  Serial.println(sensorvalue);
  int driver = map(sensorvalue, sensorMin, sensorMax, 0, 3);
  Serial.println(driver);
  switch(driver) {
    case 0:
    Serial.print("Door open");
    digitalWrite(9,HIGH);
    break;
    case 1:
    Serial.print("door close");
    digitalWrite(9,LOW);
    break;
    
  }
  delay(1000);
}
