#include <Servo.h>
#include <AccelStepper.h>
#include <SoftwareSerial.h>

//SoftwareSerial Serial1(4,5); // RX, TX (Pins bluetooth)

int stp1=9;
int dir1=10;
int stp2=11;
int dir2=12;
const int enablePin = 8;
AccelStepper stepper1(AccelStepper::DRIVER, stp1, dir1);
AccelStepper stepper2(AccelStepper::DRIVER, stp2, dir2);

Servo myservo;


struct frame_type {
  uint8_t angle;
  uint16_t step;
};

struct frame_type frame;

void setup() {
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
  stepper1.setMaxSpeed(1000);
  stepper1.move(0); 
  stepper1.setSpeed(0);

  stepper2.setMaxSpeed(1000);
  stepper2.move(0); 
  stepper2.setSpeed(0);

  myservo.attach(7);

  Serial.begin(9600);
  Serial.setTimeout(1000);
  Serial.println("");


}

void loop() {
    stepper1.run();
    stepper2.run();
  int out = Serial.readBytes((char *)(&frame), sizeof(frame));
  //Serial.println(out);
  if(out) {
    Serial.print(frame.angle);
    Serial.print(",");
    Serial.println(frame.step);
    Serial.flush();

    // /do de work
    myservo.write(frame.angle);
    stepper1.move(frame.step);
    stepper2.move(frame.step);
    delay(3000);
    Serial.println("ok");
    Serial.flush();
  }
  
  }

    

  


