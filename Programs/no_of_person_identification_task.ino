int human_counter = 0;
int last_human_counter =0;
void setup() {
  // put your setup code here, to run once:
pinMode(29,OUTPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly: 
  int sensorvalue = analogRead(2);
  Serial.print("Sensor value");
  Serial.println(sensorvalue);
  if(sensorvalue < 600 ){
    human_counter++;
  }

  if(last_human_counter != human_counter){
      if(human_counter <= 300){
        Serial.print("Human count no");
        Serial.println(human_counter);
        delay(1000);
        

  }
  if(human_counter % 100 == 0){
    Serial.println("full");
    Serial.println("next room open");
    digitalWrite(29,HIGH);
    delay(1000);
  }
  else{
    
    digitalWrite(29,LOW);
    delay(1000);
  }
 }
}

    
  
