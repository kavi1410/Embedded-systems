const int startingpoint = 2;
const int endpoint = 40;

int smallbagCounter = 0;
int mediumbagCounter = 0; 
int largebagCounter = 0;   
int bagState = 0;   
int lastbagState = 0;



void setup() {
  // put your setup code here, to run once:
  for(int bag=startingpoint ; bag<=endpoint ; bag++) {
    pinMode(bag,OUTPUT);

  }
  
    
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(29,OUTPUT);
    Serial.begin(115200);

}

void loop() {
  

  // put your main code here, to run repeatedly: 
  


  
  for(int bag=startingpoint ; bag<=endpoint ; bag++) {
    for( int speed = 0 ; speed < 255 ; speed ++){
      analogWrite(bag , speed );
      delay(3);
    }

   for (int speed = 255; speed >= 0; speed--) {
    analogWrite(bag, speed);
    delay(3);
    
   }
    bagState = digitalRead(bag);
    
    switch(bag){
    case 9 :
    Serial.println("small size Gift");
    digitalWrite(9,HIGH);
    smallbagCounter++;
    Serial.print("no of small bags");
    Serial.println(smallbagCounter);
    break;
 
    case 10 :
    Serial.println("medium size Gift");
    digitalWrite(10,HIGH);
    mediumbagCounter++;
    Serial.print("no of large bags");
    Serial.println(largebagCounter);
    break;
    
  
    case 29 :
    Serial.println("large size Gift");
    digitalWrite(29,HIGH);
    largebagCounter++;
    Serial.print("no of large bags");
    Serial.println(largebagCounter);
    break;
    }

 
   delay(1000);
  } 


}
