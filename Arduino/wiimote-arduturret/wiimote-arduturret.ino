// MultiStepper
// -*- mode: C++ -*-
//
// Control both Stepper motors at the same time with different speeds
// and accelerations. 
// Requires the AFMotor library (https://github.com/adafruit/Adafruit-Motor-Shield-library)
// And AccelStepper with AFMotor support (https://github.com/adafruit/AccelStepper)
// Public domain!

#include <AccelStepper.h>
#include <AFMotor.h>
#include <RunningAverage.h>

RunningAverage myRAx(10);
RunningAverage myRAy(10);
int xsamples = 0;
int ysamples = 0;

// two stepper motors one on each port
AF_Stepper motor1(200, 1);
AF_Stepper motor2(200, 2);

String inString = "";
int x, y, z = 0;
int currentaxis = 0;
int sx = 0;
int sy = 0;

const int rPin = 22;
const int gPin = 23;
const int bPin = 24;

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  motor1.onestep(FORWARD, INTERLEAVE);
}
void backwardstep1() {  
  motor1.onestep(BACKWARD, INTERLEAVE);
}
// wrappers for the second motor!
void forwardstep2() {  
  motor2.onestep(FORWARD, INTERLEAVE);
}
void backwardstep2() {  
  motor2.onestep(BACKWARD, INTERLEAVE);
}

// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);

void setup()
{  
    Serial.begin(9600);
    
    stepper1.setMaxSpeed(500.0);
    stepper1.setAcceleration(500.0);
    stepper1.moveTo(0);
    
    stepper2.setMaxSpeed(500.0);
    stepper2.setAcceleration(500.0);
    stepper2.moveTo(0);
   
  
    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, LOW);
    digitalWrite(bPin, LOW);
    delay(500);
    myRAx.clear();
    myRAy.clear();
    
  
}

void loop() { 

   int inChar;

  // Read serial input:
  if (Serial.available() > 0) {
    inChar = Serial.read();
  }

  if (isDigit(inChar)) {
    // convert the incoming byte to a char 
    // and add it to the string:
    inString += (char)inChar; 
  }
 
    
    if (inChar == ',') {
    // do something different for each value of currentAXES:
    switch (currentaxis) {
    case 0:    // 0 = x
      x = inString.toInt();
      
      myRAx.addValue(x);
      xsamples++;
      
    
     x = map(myRAx.getAverage(), 70, 200, 0, 800);
     
  
     stepper1.moveTo(x);
     
     if (xsamples == 20) {
       xsamples = 0;
     }
        
       
      // clear the string for new input:
      inString = ""; 
      break;
    case 1:    // 1 = y
      y = inString.toInt();
      
       myRAy.addValue(y);
      ysamples++;
      
    
     y = map(myRAy.getAverage(), 70, 200, 0, 400);
     
  
     stepper2.moveTo(y);
     
     if (ysamples == 20) {
       ysamples = 0;
     }
        
      // clear the string for new input:
      inString = ""; 
      break;
    }
    currentaxis++;
    }
  // if you get a newline, you know you've got
  // the last axis 
  if (inChar == ')') {
    z = inString.toInt();
   

     inString = ""; 
    // reset the axis counter:
    currentaxis = 0;
    
}

if (inChar == 'F') {
  
  
    
    digitalWrite(rPin, HIGH);
    
    delay(1);
    
    digitalWrite(rPin, LOW);
   
    digitalWrite(gPin, HIGH);
    
    delay(1);
    
    digitalWrite(gPin, LOW);
   
    digitalWrite(bPin, HIGH);
    
    delay(1);
    
    digitalWrite(bPin, LOW);
    
    
  
}

      
stepper1.run();
stepper2.run();

      
      
}
