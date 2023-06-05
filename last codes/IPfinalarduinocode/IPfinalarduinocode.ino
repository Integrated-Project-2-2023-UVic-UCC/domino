#include <Servo.h>          // including libraries 
#include <AccelStepper.h>
#include <SoftwareSerial.h>

// SoftwareSerial Serial1(4,5); // RX, TX (Pins bluetooth)
int angle = 0;
int stp1 = 9;                  //pin passos motor pas a pas
int dir1 = 10;                 //pin direccio motor pas a pas
int stp2 = 11;                 //pin passos motor pas a pas
int dir2 = 12;                 //pin direccio motor pas a pas
int DistanciaRecorreguda = 0;  //Contador de passos total
int primermov = 0;             //Valor de passos a donar per al primer moviment del recoregut abans de girar la storage wheel
int secmov = 0;                //Valor de passos a donar per al segon moviment del recoregut depres de girar la storage wheel
int Rotacio = 7000;            //Valor de passos que es nececiten per buidar una columna de l'estorage wheel
int framestep = 0;
bool secmoviment = false;  //Variable que avisa si el robot esta fent la segona part del recoregut depres de girar la storage wheel
bool STOPPROGRAM = false;  //Variable que para el programa quan ja no queden mes peces
bool firsttime = true;     //Variable que mira si es rep senyal del python si rep valor permet executar el codi
bool direccionat = true;
bool stop = false;
int Anglesstorage = 0;
int valorempuje = 110;    //valor de rotacio del servo que empeny les peces
const int enablePin = 8;  //pin d'activacio motors pas a pas
bool parar;
int Reload = 1000;
//Declarem els motors pas a pas
AccelStepper stepper1(AccelStepper::DRIVER, stp1, dir1);
AccelStepper stepper2(AccelStepper::DRIVER, stp2, dir2);
//Declarem els servomotors
Servo myservoReload;
Servo myservoDirection;
Servo myservoEmpuje;
int out;
//Declarem la estructura de rebut
struct frame_type {
  uint8_t angle;
  uint16_t step;
};

struct frame_type frame;

void setup() {
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);  //activem motors
  stepper1.setMaxSpeed(500);     //valors inicials dels motors
  stepper1.move(0);
  stepper1.setAcceleration(300);

  stepper2.setMaxSpeed(500);
  stepper2.move(0);
  stepper2.setAcceleration(300);
  //Declarem pins per als servos i els hi donem els valors inicials
  myservoReload.attach(7);
  myservoDirection.attach(5);
  myservoEmpuje.attach(3);
  myservoDirection.write(90);
  myservoEmpuje.write(94);
  myservoReload.write(0);

  Serial.begin(9600);
  Serial.setTimeout(1000);
  out = Serial.readBytes((char *)(&frame), sizeof(frame));
}

void loop() {
  //com que si el programna no rep res del bluetoth assumeix que tot es 0 al principi mentres rebi 0 no executem res quan rebi algo diferent a 0 cambiem el valor de la variable i peretem que es mogui
  if (stop == true){
    myservoEmpuje.write(94);
  }

  if (stop == false){
    
  
    
    if (frame.angle == 0 && firsttime == true) {
      out = Serial.readBytes((char *)(&frame), sizeof(frame));
      if (frame.angle != 0) {
        firsttime = false;
      }
    }
    if (firsttime == false) {
      if (STOPPROGRAM == false) {
        stepper1.run();  //Executa el valor donat a la funcio move() amb la velocitat i la acceleracio del void setup
        stepper2.run();
        myservoEmpuje.write(65);
      }


      if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0) { // main part of the program that keeps looping ultil the the distanceToGo for the movement is 0
        myservoEmpuje.write(94);
        if (secmoviment == false && direccionat == false) {
          Serial.println("ok");
          int out = Serial.readBytes((char *)(&frame), sizeof(frame));  // reads the buffer
          Serial.flush();
          if ((frame.angle ==11) && (frame.step == 1111)) {  // specific values to stop the program from the python when the path ends
            stop = true;
            
           }
          DistanciaRecorreguda = DistanciaRecorreguda + (frame.step*3) + 950;  // counter to count the distance that been walked 
          Serial.println("DistanciaRecorreguda");
          Serial.print(DistanciaRecorreguda);
          direccionat = false;
        }
        if (direccionat == false) {    // directioning the front servo 
          if (frame.angle <= 55) {
            myservoDirection.write(55);
          } else if (frame.angle >= 125) {
            myservoDirection.write(125);
          } else {
            myservoDirection.write(frame.angle);          
          }
          delay(500);
          stepper1.move(-950);  //
          stepper2.move(950);
          direccionat = true;
        } else if (secmoviment == true) {    //if storage have to spin storage spin
          Anglesstorage = Anglesstorage + 45;
          Serial.println("Anglesstorage");
          Serial.print(Anglesstorage);
          myservoReload.write(Anglesstorage); //storage spin
          if (Anglesstorage >= 180) {
            myservoEmpuje.write(94);
            stop = true; 
            Serial.println("S'han acabat les peces");
          }
          myservoDirection.write(90);
          delay(500);
          myservoEmpuje.write(65);
          stepper1.move(-secmov);
          stepper2.move(secmov);
          secmoviment = false;
          direccionat = false;
        } else if (DistanciaRecorreguda > Rotacio) {

          Serial.println("Rotacio");
          secmov = DistanciaRecorreguda - Rotacio;
          primermov = (frame.step*3) - secmov;
          myservoDirection.write(90);
          myservoEmpuje.write(94);
          delay(500);
          //stepper1.move(primermov);
          //stepper2.move(-primermov);
          secmoviment = true;
          DistanciaRecorreguda = DistanciaRecorreguda - Rotacio;
        } else {
          if (direccionat == true) {
            myservoDirection.write(90);
            delay(500);
            framestep = (frame.step*3) * (-1);
            stepper1.move(framestep);
            stepper2.move(frame.step*3);
            Serial.println(frame.step*3);
            direccionat = false;
          }
        }
      }
    }
  }
}
