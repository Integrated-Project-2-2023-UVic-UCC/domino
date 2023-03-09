#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pos = 0;
  myservo.write(pos);
  delay(1000);
  pos = 360;
  myservo.write(pos);

  
 

  
}

void loop() {
 
 
  
  
}
