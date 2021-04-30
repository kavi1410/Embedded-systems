const int startingpoint = 2;
const int endpoint = 40;



void setup() {
  // put your setup code here, to run once:
  for(int bag=startingpoint ; bag<=endpoint ; bag++) {
    pinMode(bag,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(29,OUTPUT);
  }
Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly: 
  for(int bag=startingpoint ; bag<=endpoint ; bag++) {
    for( int speed = 0 ; speed < 255 ; speed ++){
      analogWrite(bag , speed );
      delay(1000);
    }

   for (int speed = 255; speed >= 0; speed--) {
    analogWrite(bag, speed);
    delay(1000);
    
   }
     if( bag == 9 ){
      Serial.println(" Normal scanning ");
      delay(1000);
    }
    
    if( bag == 10 ){
      Serial.print("  Weapon scanning");
      delay(1000);
    }
    if(bag == 29){
      Serial.print(" Drugs scanning ");
      delay(1000);
      }
 
   delay(3000);
  }
  
}
