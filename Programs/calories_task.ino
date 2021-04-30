const int Steps = PUSH2;
const int led1 = RED_LED;


int StepsCounter=0; 
int StepsState = 0;
int LastStepsState=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Steps,INPUT_PULLUP);
  pinMode(led1,OUTPUT);

  Serial.begin(115200);

}

void loop() {
  
  // put your main code here, to run repeatedly: 

  StepsState = digitalRead(Steps);
  
  if (StepsState != LastStepsState) {
    if (StepsState == HIGH) {
      StepsCounter++;
      Serial.println ("person detected");
      Serial.print("number of steps = ");
      Serial.print(StepsCounter);
    }
  }
    else {
      Serial.print("person not detected");
    }
  
   StepsState = LastStepsState;
  
  if (StepsCounter % 4 == 0) {
    Serial.print("4kg calories decrese");
    digitalWrite(led1 , HIGH);
  }
  else{
    digitalWrite(led1 , LOW);
    
  }
  }
 
