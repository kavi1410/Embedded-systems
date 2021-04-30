void setup() {
  // put your setup code here, to run once:
  pinMode(29,OUTPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly: 
  int sensorvalue = analogRead(2);
  Serial.println(sensorvalue);
  if(sensorvalue < 600) {
    Serial.println("someone touch the car");
   digitalWrite(29,HIGH);
   delay(1000);
  }
  else{
  digitalWrite(29,LOW);
  delay(1000);
 }
}
