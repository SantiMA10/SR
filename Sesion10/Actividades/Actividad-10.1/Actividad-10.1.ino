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
  int irDer = digitalRead(pinIrDer);
  int irIzq = digitalRead(pinIrIzq);

  //horario -> 0
  //antihorario -> 180
  
  //Adelante
  if (irDer == LINEA && irIzq == LINEA){
    servoIzq.write(0); 
    servoDer.write(180);
  }
  //Izquierda
  else if (irDer != LINEA && irIzq == LINEA){
    servoIzq.write(90); 
    servoDer.write(50);
  }
  //Derecha
  else if (irDer == LINEA && irIzq != LINEA){
    servoIzq.write(140); 
    servoDer.write(90);
  }
  //Atras
  else if (irDer != LINEA && irIzq != LINEA){
    servoIzq.write(90); 
    servoDer.write(90);
  }


}
