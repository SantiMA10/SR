#include <Servo.h>

int NO_LINEA = 1;
int LINEA = 0;

Servo servoIzq;
Servo servoDer;

int pinServoDer = 9;
int pinServoIzq = 8;
int pinIrDer = 3;
int pinIrIzq = 2;


void setup() {
  pinMode( pinIrDer , INPUT);
  pinMode( pinIrIzq , INPUT);

  servoIzq.attach(pinServoIzq);
  servoDer.attach(pinServoDer);


}

void loop() {
  servoIzq.write(0); 
  servoDer.write(180);
  
  if (digitalRead(pinIrDer) == LINEA || digitalRead(pinIrIzq) == LINEA){
    servoIzq.write(180); 
    servoDer.write(180);
    delay(1000);
  }


}
