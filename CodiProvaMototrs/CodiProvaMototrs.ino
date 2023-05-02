#include <AccelStepper.h> //Llibreria per als Stepmotors
int stp1=9;
int dir1=10;
int stp2=11;
int dir2=12;
const int enablePin = 8;
AccelStepper stepper1(AccelStepper::DRIVER, stp1, dir1);
AccelStepper stepper2(AccelStepper::DRIVER, stp2, dir2);
void setup() {
  // put your setup code here, to run once:
pinMode(enablePin, OUTPUT);
digitalWrite(enablePin, LOW);
stepper1.setMaxSpeed(1000);
stepper1.move(-6000); 

stepper2.setMaxSpeed(1000);
stepper2.move(-6000); 

}

void loop() {
  // put your main code here, to run repeatedly:
    stepper1.run();
    stepper2.run();
}
