#include <Servo.h>
#include <AccelStepper.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(4,5); // RX, TX (Pins bluetooth)

int stp1=9;
int dir1=10;
int stp2=11;
int dir2=12;
int DistanciaRecorreguda=0;
int Anglesstorage=0;
const int enablePin = 8;
int Reload=1000;
bool parar=true;

AccelStepper stepper1(AccelStepper::DRIVER, stp1, dir1);
AccelStepper stepper2(AccelStepper::DRIVER, stp2, dir2);

Servo myservoReload;
Servo myservoDirection;
Servo myservoEmpuje;


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

  myservoReload.attach(7);
  myservoDirection.attach(5);
  myservoEmpuje.attach(3);

  Serial1.begin(9600);
  Serial1.setTimeout(1000);
  Serial1.println("");
}

void loop() {
  int out = Serial1.readBytes((char *)(&frame), sizeof(frame));
  if(parar==true){
    stepper1.run();
    stepper2.run();
  }
  //Serial.println(out);
  if(out) {
    Serial1.print(frame.angle);
    Serial1.print(",");
    Serial1.println(frame.step);
    Serial1.flush();

    // /do de work
    myservoDirection.write(frame.angle);
    stepper1.move(frame.step);
    stepper2.move(frame.step);
    DistanciaRecorreguda=DistanciaRecorreguda+frame.step;
    if (DistanciaRecorreguda>=Reload){
    parar=true;
     DistanciaRecorreguda=DistanciaRecorreguda-Reload;
     stepper1.setCurrentPosition(0);
    stepper2.setCurrentPosition(0);
     Anglesstorage=Anglesstorage+45;
     if (Anglesstorage < 360 ) {
       parar=false;
     }
     myservoReload.write(Anglesstorage);
//If thies not works try with an interruption
    delay(1000);
     stepper1.move(DistanciaRecorreguda);
    stepper2.move(DistanciaRecorreguda);
  


    }
    delay(3000);
    Serial1.println("ok");
    Serial1.flush();

  
  }
}
    

  


