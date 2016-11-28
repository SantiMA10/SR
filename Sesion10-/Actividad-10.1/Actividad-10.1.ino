#include <Servo.h>

int NO_LINEA = 1;
int LINEA = 0;

int PIN_IZQ = 0;
int PIN_C_IZQ = 1;
int PIN_C_DER = 2;
int PIN_DER = 3;

Servo servoIzq;
Servo servoDer;

int pinServoDer = 9;
int pinServoIzq = 8;

int pinIrDerCen = 3;
int pinIrIzqCen = 2;
int pinIrDer = 11;
int pinIrIzq = 10;

int pinesSensores[] = {10, 2, 3, 11};
int sensor[4];

int compensacion = 10;

int HORARIO = 110;
int ANTIHORARIO = 70;

int PARAR = 90;

void setup() {
  Serial.begin(9600);
  pinMode( pinIrDerCen , INPUT);
  pinMode( pinIrIzqCen , INPUT);
  pinMode( pinIrDer , INPUT);
  pinMode( pinIrIzq , INPUT);

  servoIzq.attach(pinServoIzq);
  servoDer.attach(pinServoDer);
  //delay(10000);
}

void loop() {

  actualizarTodosLosSensores();

  if (sensor[PIN_C_IZQ] == LINEA && sensor[PIN_C_DER] == LINEA
      && sensor[PIN_IZQ] == NO_LINEA && sensor[PIN_DER] == NO_LINEA) {
    servoIzq.write(ANTIHORARIO - compensacion);
    servoDer.write(HORARIO);
  }
  else if (sensor[PIN_C_IZQ] == NO_LINEA && sensor[PIN_C_DER] == LINEA
           && sensor[PIN_IZQ] == NO_LINEA && sensor[PIN_DER] == NO_LINEA) {
    servoIzq.write(HORARIO - compensacion);
    servoDer.write(HORARIO);
  }
  else if (sensor[PIN_C_IZQ] == LINEA && sensor[PIN_C_DER] == NO_LINEA
           && sensor[PIN_IZQ] == NO_LINEA && sensor[PIN_DER] == NO_LINEA) {
    servoIzq.write(ANTIHORARIO - compensacion);
    servoDer.write(ANTIHORARIO);
  }
  else if (sensor[PIN_C_IZQ] == NO_LINEA && sensor[PIN_C_DER] == NO_LINEA
           && sensor[PIN_IZQ] == NO_LINEA && sensor[PIN_DER] == NO_LINEA) {
    servoIzq.write(ANTIHORARIO);
    servoDer.write(ANTIHORARIO);
  }
  else if (sensor[PIN_C_IZQ] == LINEA && sensor[PIN_C_DER] == LINEA
           && sensor[PIN_IZQ] == LINEA && sensor[PIN_DER] == NO_LINEA) {
    delay(500);
    girarIzquierda();
  }
  else if (sensor[PIN_C_IZQ] == LINEA && sensor[PIN_C_DER] == LINEA
           && sensor[PIN_IZQ] == NO_LINEA && sensor[PIN_DER] == LINEA) {
    delay(500);
    girarDerecha();
  }
  else if (sensor[PIN_C_IZQ] == LINEA && sensor[PIN_C_DER] == LINEA
           && sensor[PIN_IZQ] == LINEA && sensor[PIN_DER] == LINEA) {
    delay(500);
    actualizarTodosLosSensores();
    if (sensor[PIN_C_IZQ] == LINEA && sensor[PIN_C_DER] == LINEA
        && sensor[PIN_IZQ] == LINEA && sensor[PIN_DER] == LINEA) {
      servoIzq.write(PARAR);
      servoDer.write(PARAR);
    }
    else {
      girarDerecha();
    }
  }

}


void actualizarTodosLosSensores() {
  for (int i = 0; i < 4; i++) {
    sensor[i] =  digitalRead(pinesSensores[i]);
  }

  // 4 lecturas adicionales
  // Se guardan las que detectan línea en cualquiera de los 4 barridos
  for (int i = 0; i < 4; i++) {
    delay(20); // Delay con el movimiento actual

    for (int i = 0; i < 4; i++) {
      if (digitalRead(pinesSensores[i]) == LINEA)
        sensor[i] = LINEA;
    }
  }
}

void girarDerecha() {
  // girar hacia la derecha
  servoDer.write(ANTIHORARIO);
  servoIzq.write(ANTIHORARIO);
  delay(400); // Pequeño delay para que le dé tiempo a salir de su carril actual
  // Si no puede que este ya en un carril y detectaría línea

  boolean carrilEncontrado = false;
  while (!carrilEncontrado) {
    int Sensor2 = digitalRead(pinIrIzqCen);
    int Sensor3 = digitalRead(pinIrDerCen);

    if ( Sensor2 == LINEA && Sensor3 == LINEA ) {
      carrilEncontrado = true;
    }
  }

  // Parar
  servoIzq.write(ANTIHORARIO - compensacion);
  servoDer.write(HORARIO);
}

void girarIzquierda() {
  // girar hacia la derecha
  servoDer.write(HORARIO);
  servoIzq.write(HORARIO);
  delay(400); // Pequeño delay para que le dé tiempo a salir de su carril actual
  // Si no puede que este ya en un carril y detectaría línea

  boolean carrilEncontrado = false;
  while (!carrilEncontrado) {
    int Sensor2 = digitalRead(pinIrIzqCen);
    int Sensor3 = digitalRead(pinIrDerCen);

    if ( Sensor2 == LINEA && Sensor3 == LINEA ) {
      carrilEncontrado = true;
    }
  }

  // Parar
  servoIzq.write(ANTIHORARIO - compensacion);
  servoDer.write(HORARIO);
}
