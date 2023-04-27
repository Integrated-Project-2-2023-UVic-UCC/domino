#include <Servo.h>

Servo servo;

struct frame_type {
  uint8_t angle;
  uint16_t distance;
};

struct frame_type frame;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);
  Serial.println("");
}

void loop() {

  int out = Serial.readBytes((char *)(&frame), sizeof(frame));
  //Serial.println(out);
  if(out) {
    Serial.print(frame.angle);
    Serial.print(", ");
    Serial.println(frame.distance);
    Serial.flush();

    // /do de work
    delay(3000);

    Serial.println("ok");
    Serial.flush();
  }
  //delay(1);
  // while (Serial.available() >= 1){
  //   int identifier = Serial.read();

  //   if (identifier == 1) {
  //     int valor = Serial.read();
  //     Serial.print("Value recieved (1 byte) ");
  //     Serial.println(valor);
  //   } else if (identifier == 2) {
  //     byte bytesRecebidos[2];
  //     Serial.readBytes(bytesRecebidos, 2);
  //     int valor = (bytesRecebidos[1] << 8) | bytesRecebidos[0];
  //     Serial.print("Value recieved (2 bytes): ");
  //     Serial.println(valor);
  //   } else {
  //     Serial.println("invalid identifier");
  //   }

  //  }
  }

    

  


