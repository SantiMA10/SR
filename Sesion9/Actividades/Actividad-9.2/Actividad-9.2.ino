#include <Servo.h>

int NO_LINEA = 1;
int LINEA = 0;

Servo servoIzq;
Servo servoDer;

int pinServoDer = 9;
int pinServoIzq = 8;
int pinIrDer = 3;
int pinIrIzq = 2;

struct Salida {
  boolean activo = false;
  int servoIzq = -1;
  int servoDer = 90;
};

Salida sComp1 ;
Salida sComp2 ;
Salida sComp3 ;

double control = 0.0;
int reiniciar = 0;

void setup() {
  Serial.begin(9600);
  pinMode( pinIrDer , INPUT);
  pinMode( pinIrIzq , INPUT);

  servoIzq.attach(pinServoIzq);
  servoDer.attach(pinServoDer);
}

void loop() {
  int valorSensorIzq = digitalRead(pinIrIzq);
  int valorSensorDer = digitalRead(pinIrDer);
  //Serial.println("Izq: " + String(valorSensorIzq) + " Der: " + String(valorSensorDer) + " -------------------------------------------------------------");

  comp1_EntratEnPista(valorSensorIzq, valorSensorDer);
  if ( sComp1.activo ) {
    // Sí este está activo hay que entrar en pista

    servoIzq.write(sComp1.servoIzq);
    servoDer.write(sComp1.servoDer);
    return;
  }

  comp2_CorregirTrayectoria(valorSensorIzq, valorSensorDer);
  if ( sComp2.activo ) {
    // Sí este está activo hay que entrar en pista

    servoIzq.write(sComp2.servoIzq);
    servoDer.write(sComp2.servoDer);
    return;
  }

  comp3_Avanzar(valorSensorIzq, valorSensorDer);
  if ( sComp3.activo ) {
    // Sí este está activo hay que entrar en pista

    servoIzq.write(sComp3.servoIzq);
    servoDer.write(sComp3.servoDer);
    return;
  }


}

void comp1_EntratEnPista(int valorSensorIzq, int valorSensorDer) {
  sComp1.activo = false;
  if ( valorSensorIzq == NO_LINEA && valorSensorDer == NO_LINEA ) {
    sComp1.activo = true;
    control += 0.01;
    sComp1.servoIzq = 0;
    sComp1.servoDer = 90 + control;
    
  }
}

void comp2_CorregirTrayectoria(int valorSensorIzq, int valorSensorDer) {
  control = 0.0;
  sComp2.activo = false;
  if ( valorSensorIzq == LINEA && valorSensorDer == NO_LINEA ) {
    sComp2.activo = true;
    sComp2.servoIzq = 50;
    sComp2.servoDer = 90;
  }
  if ( valorSensorIzq == NO_LINEA && valorSensorDer == LINEA ) {
    sComp2.activo = true;
    sComp2.servoIzq = 90;
    sComp2.servoDer = 140;
  }
}

void comp3_Avanzar(int valorSensorIzq, int valorSensorDer) {
  control = 0.0;
  sComp3.activo = false;
  if ( valorSensorIzq == LINEA && valorSensorDer == LINEA) {
    sComp3.activo = true;
    sComp3.servoIzq = 0;
    sComp3.servoDer = 180;
  }
}

