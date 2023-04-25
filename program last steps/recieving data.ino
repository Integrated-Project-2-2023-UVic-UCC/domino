#include <SoftwareSerial.h>
#include <Servo.h>
#include <Stepper.h>
#define SERVO_LEFT_POSITION 0;
#define SERVO_RIGHT_POSITION 180;

SoftwareSerial Serial1(10, 11); // RX, TX

Servo direction; 

void setup() {
  Serial1.begin(9600);
  Serial1.println("end setup");
  
  // Set up the stepper motor
  Stepper.setMaxSpeed(MAX_SPEED);
  stepper.setAcceleration(ACCELERATION);
  stepper.setEnablePin(4);
  stepper.enableOutputs();

  // Set up the servo motor
  servo.attach(SERVO_PIN);
}

void loop() {
  cmd = Serial1.read();
  direction.write(cmd);
  delay(300)
  cmd = Serial1.read();
  stepper.moveTo(cmd);
  Serial1.println("+")
  delay(1000);


}
