//constants
static const int IN = LOW;
static const int OUT = HIGH;
static const int pulseDelayTime = 6;

//pins
//int indexPin = 2; //8 on the drive INDEX
int track0Pin = 3; //26 on the drive. TRACK 0
int dirPin = 6; //18 on the drive. DIRECTION
int stepPin = 7; //20 on the drive. STEP
int motorEnableBPin = 9; //16 on the drive. MOTOR ENABLE B
int driveSelectPin = 10; //12 on the drive. DRIVE SEL B
int bootSeek0 = 1;
int serialByte=0;

unsigned long motorSpinTime = 1000UL; //in ms



void setup() {

  //initial delay
  delay(30);

  //setup serial monitor
  Serial.begin(9600);      

  //setup pins.
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(motorEnableBPin, OUTPUT);
  pinMode(driveSelectPin, OUTPUT);
  //pinMode(indexPin, INPUT);
  pinMode(track0Pin, INPUT_PULLUP);
  

  //turn the motor/select off initially
  digitalWrite(motorEnableBPin, HIGH);
  digitalWrite(driveSelectPin, HIGH);
  digitalWrite(track0Pin, HIGH);
  digitalWrite(dirPin,HIGH);

//  //print state here.
//  printState("Setup done.");
//  driveSelectPin = motorEnableBPin;
//  //spin the disk some.
//  printState("Begin to spin motor");
//  spinMotorForThisManyMs(motorSpinTime);
//  spinMotorForThisManyMs(motorSpinTime);
//  printState("Done spinning motor");
//
//  //step read/write head all the way in.
//  stepAllTheWayIn();
//
//  //spin the disk some more.
//  printState("Begin to spin motor");
//  spinMotorForThisManyMs(motorSpinTime);
//  spinMotorForThisManyMs(motorSpinTime);
//  printState("Done spinning motor");
//
//  //step read/write head all the way out.
//  stepAllTheWayOut();
//
//  //spin the disk even more.
//  printState("Begin to spin motor");
//  spinMotorForThisManyMs(motorSpinTime);
//  spinMotorForThisManyMs(motorSpinTime);
//  printState("Done spinning motor");
//
//  //never completes.
//  waitForIndex();
}

//move the head towards the outside a little
void stepOut() {
  digitalWrite(dirPin,HIGH);
  stepPulse();
}

//move the head towards the center a little
void stepIn() {
  digitalWrite(dirPin,LOW);
  stepPulse();
}

//pulse the step pin
void stepPulse() {
  digitalWrite(stepPin,LOW);
  delay(pulseDelayTime);
  digitalWrite(stepPin,HIGH);
}

void stepAllTheWayIn() {
  for(int i=0;i<80;i++) {
    stepIn();
    }
  }

void stepAllTheWayOut() {
  for(int i=0;i<80;i++) {
    delay(300);
    stepOut();
    }
  }

void loop() {

  //On power on, step out until track 0 signal (active low) then start a counter to make sure steps in don't exceed 80. From there, always make sure direction is reversed 
  while (track0Pin == HIGH && bootSeek0 == 1){
    digitalWrite(motorEnableBPin,LOW);
    digitalWrite(driveSelectPin,LOW);
    stepOut();
      if (track0Pin == LOW){
        bootSeek0=0;
        digitalWrite(stepPin,HIGH);
        digitalWrite(motorEnableBPin,HIGH);
        digitalWrite(driveSelectPin,HIGH);
        break;
      }
    }

    if (Serial.available() > 0) {
      serialByte = Serial.read();
        if (serialByte == 50){ //2
          digitalWrite(motorEnableBPin,LOW);
          digitalWrite(driveSelectPin,LOW);
        }
      
        else if (serialByte == 49){//1
          digitalWrite(motorEnableBPin,HIGH);
          digitalWrite(driveSelectPin,HIGH);
        }

        if (serialByte == 51){//3
          digitalWrite(motorEnableBPin,LOW);
          digitalWrite(driveSelectPin,LOW);
          stepIn();          
        }
      
//        else if (serialByte == 49){//1
//          digitalWrite(dirPin,HIGH);
//          digitalWrite(stepPin,HIGH);
//          digitalWrite(driveSelectPin,HIGH);          
//        }

        if (serialByte == 52){//4
          digitalWrite(motorEnableBPin,LOW);
          digitalWrite(driveSelectPin,LOW);
          stepOut();         
        }
      
//        else if (serialByte == 49){//1
//          digitalWrite(dirPin,HIGH);
//          digitalWrite(stepPin,HIGH);
//          digitalWrite(driveSelectPin,HIGH);          
//        }

//        if (digitalRead(track0Pin) == LOW){
//          serialByte = 53;
//        }
        
      }

      
//  Serial.println(serialByte); 
  
}

