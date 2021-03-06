#include <Servo.h>

#define boton_pin 13 // pin digital para el botón
#define Y_pinY A0 // pin analógico para leer eje X
#define X_pinX A1 // pin analógico para leer eje X

#define DERECHA 0
#define IZQUIERDA 1
#define PARADA 2

#define sizearray 100

int Xder = 8;
int Xizq = 13;

int Yab = 7;
int Yar = 11;

Servo servoX;
int pinServoX = 5;

int posicion[sizearray];
long tiempo[sizearray];
int i;

long tiempoInicial;

int modo;
int modoAnterior;
int grabando;
int reproduciendo;
int moviendo;

void setup() {
  Serial.begin(9600);
  servoX.attach(pinServoX);

  pinMode(Xder, INPUT);

  modo = PARADA;
  grabando = 0;
  reproduciendo = 0;
  moviendo = 0;
  i = 0;
}

void loop() {
  int valorX = analogRead(X_pinX);
  //Serial.println("X: "+String(valorX));

  if (valorX < 412) {
    servoX.write(180);
    moviendo = 0;

    if (grabando == 1 && modo != IZQUIERDA) {
      modoAnterior = modo;
      grabar();
      tiempoInicial = millis();
    }
    modo = IZQUIERDA;

  }
  else if (valorX > 412 && valorX < 612) {
    servoX.write(90);

    if (grabando == 1 && modo != PARADA) {
      modoAnterior = modo;
      grabar();
      tiempoInicial = millis();
    }
    modo = PARADA;
  }
  else if (valorX > 612) {
    servoX.write(0);

    if (grabando == 1 && modo != DERECHA) {
      modoAnterior = modo;
      grabar();
      tiempoInicial = millis();
    }
    modo = DERECHA;

  }

  if (Serial.available() != 0) {

    String comando = Serial.readString();

    if (comando == "g") {
      Serial.println("Grabando");
      grabando = 1;
      reproduciendo = 0;
      i = 0;
      irA0();
      modo = PARADA;
      tiempoInicial = millis();
    }

    if (comando == "r") {
      Serial.println("Reproduciendo");
      grabando = 0;
      reproduciendo = 1;
      irA0();
    }

  }

  if (reproduciendo == 1) {
    Serial.println("reproducion");
    int j;
    for (j = 0; j < i; j++) {
      Serial.println("tiempo[j]:" + String(tiempo[j]) + ", posicion[j]: " + String(posicion[j]));
      if (posicion[j] == DERECHA) {
        servoX.write(0);
        delay(tiempo[j]);
      }
      else if (posicion[j] == IZQUIERDA) {
        servoX.write(180);
        delay(tiempo[j]);
      }
      else if (posicion[j] == PARADA) {
        servoX.write(90);
        delay(tiempo[j]);
      }
    }
    reproduciendo = 0;
  }

}

void grabar() {
  int tiempoFin = millis() - tiempoInicial;
  posicion[i] = modoAnterior;
  tiempo[i] = tiempoFin;
  Serial.println("tiempoInicial: " + String(tiempoInicial) + ", tiempoFin:" + String(tiempoFin) + " tiempo[i]:" + String(tiempo[i]) + ", posicion[i]: " + String(posicion[i]));
  i++;
}

void irA0() {
  servoX.write(0);
  while (digitalRead(Xder) == HIGH) { }
  servoX.write(90);
}

