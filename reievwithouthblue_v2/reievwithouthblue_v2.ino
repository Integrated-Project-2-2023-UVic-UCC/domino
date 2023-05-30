#include <Servo.h>
#include <AccelStepper.h>
#include <SoftwareSerial.h>

// SoftwareSerial Serial1(4,5); // RX, TX (Pins bluetooth)
int angle = 0;
int stp1 = 9;
int dir1 = 10;
int stp2 = 11;
int dir2 = 12;
int DistanciaRecorreguda = 0;
int primermov = 0;
int secmov = 0;
int Rotacio = 0;
bool secmoviment = false;
bool STOPPROGRAM = false;
int Anglesstorage = 0;
const int enablePin = 8;
int Reload = 1000;
AccelStepper stepper1(AccelStepper::DRIVER, stp1, dir1);
AccelStepper stepper2(AccelStepper::DRIVER, stp2, dir2);
Servo myservoReload;
Servo myservoDirection;
Servo myservoEmpuje;
int out;
struct frame_type {
  uint8_t angle;
  uint16_t step;
};

struct frame_type frame;

void setup() {
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
  stepper1.setMaxSpeed(2000);
  stepper1.move(0);
  stepper1.setAcceleration(500);   //Hauriem de baixar la velocitat i tenir acceleracio molt alta perque no es noti
  //stepper1.setSpeed(0);

  stepper2.setMaxSpeed(2000);
  stepper2.move(0);
  stepper2.setAcceleration(500);
  //stepper2.setSpeed(0);

  myservoReload.attach(7);
  myservoDirection.attach(5);
  myservoEmpuje.attach(3);

  Serial.begin(9600);
  Serial.setTimeout(1000);
  Serial.println("");
  out = Serial.readBytes((char *)(&frame), sizeof(frame));
}

void loop() {
  if (STOPPROGRAM == false) {
    stepper1.run();
    stepper2.run();
  }


  if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0) {
    if (secmoviment == false) {
      Serial.println("ok");
      int out = Serial.readBytes((char *)(&frame), sizeof(frame));
      Serial.flush();
      DistanciaRecorreguda = DistanciaRecorreguda + frame.step;
    }
    if (secmoviment == true) {
      Anglesstorage = Anglesstorage + 45;
      myservoReload.write(Anglesstorage);
      if (Anglesstorage >= 360) {
        STOPPROGRAM = true;
      }
      myservoDirection.write(frame.angle);
      delay(500);
      stepper1.move(secmov);
      stepper2.move(secmov);
      secmoviment = false;
    } else if (DistanciaRecorreguda > Rotacio) {
      secmov = DistanciaRecorreguda - Rotacio;
      primermov = frame.step - secmov;
      myservoDirection.write(frame.angle);
      delay(500);
      stepper1.move(primermov);
      stepper2.move(primermov);
      secmoviment = true;
      DistanciaRecorreguda = DistanciaRecorreguda - Rotacio;
    } else {
      myservoDirection.write(frame.angle);
      delay(500);
      stepper1.move(frame.step);
      stepper2.move(frame.step);
      Serial.println(frame.step);
    }
  }
}
