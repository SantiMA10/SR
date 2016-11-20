#include <Servo.h>

#define boton_pin 13 // pin digital para el botón
#define Y_pinY A0 // pin analógico para leer eje X
#define X_pinX A1 // pin analógico para leer eje X
#define X_pinP A3

#define DERECHA 0
#define IZQUIERDA 1
#define PARADA 2
#define ARRIBA 3
#define ABAJO 4
#define ABRIR 5
#define CERRAR 6

#define GMAX 110
#define GMIN 10

#define sizearray 100

int Xder = 8;
int Yab = 12;

Servo servoX;
int pinServoX = 7;

Servo servoY;
int pinServoY = 10;

Servo servoP;
int pinServoP = 9;

int gradosPinza = 0;

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
  servoY.attach(pinServoY);
  servoP.attach(pinServoP);

  pinMode(Xder, INPUT);
  pinMode(Yab, INPUT);

  modo = PARADA;
  grabando = 0;
  reproduciendo = 0;
  i = 0;
  moviendo = 0;
}

void loop() {

  if (moviendo != 2 && moviendo != 3) {

    int valorX = analogRead(X_pinX);
    //Serial.println("X: "+String(valorX));

    if (valorX < 412) {
      servoX.write(180);
      moviendo = 1;
      if (grabando == 1 && modo != IZQUIERDA) {
        modoAnterior = modo;
        grabar();
        tiempoInicial = millis();
      }
      modo = IZQUIERDA;
    }
    else if (valorX > 412 && valorX < 612) {
      servoX.write(90);
      servoY.write(90);
      moviendo = 0;
      if (grabando == 1 && modo != PARADA) {
        modoAnterior = modo;
        grabar();
        tiempoInicial = millis();
      }
      modo = PARADA;
    }
    else if (valorX > 612) {
      servoX.write(0);
      moviendo = 1;
      if (grabando == 1 && modo != DERECHA) {
        modoAnterior = modo;
        grabar();
        tiempoInicial = millis();
      }
      modo = DERECHA;
    }
  }

  if (moviendo != 1 && moviendo != 3) {
    int valorY = analogRead(Y_pinY);
    //Serial.println("Y: "+String(valorY));

    if (valorY < 412) {
      servoY.write(0);
      moviendo = 2;
      if (grabando == 1 && modo != ARRIBA) {
        modoAnterior = modo;
        grabar();
        tiempoInicial = millis();
      }
      modo = ARRIBA;
    }
    else if (valorY > 412 && valorY < 612) {
      servoX.write(90);
      servoY.write(90);
      moviendo = 0;
      if (grabando == 1 && modo != PARADA) {
        modoAnterior = modo;
        grabar();
        tiempoInicial = millis();
      }
      modo = PARADA;
    }
    else if (valorY > 612) {
      servoY.write(180);
      moviendo = 2;
      if (grabando == 1 && modo != ABAJO) {
        modoAnterior = modo;
        grabar();
        tiempoInicial = millis();
      }
      modo = ABAJO;
    }
  }
  if (moviendo != 2 && moviendo != 1) {
    int X = analogRead(X_pinP);
    //Serial.println("P: "+String(X));

    // Aumentar / reducir grados segun X-Joystick
    // Joystick de 0 a 1024, desechamos las posiciones centrales
    if (X > 700 ) {
      if ( gradosPinza < GMAX) {
        gradosPinza = gradosPinza + 3;
        moviendo = 3;
        if (grabando == 1 && modo != CERRAR) {
          modoAnterior = modo;
          grabar();
          tiempoInicial = gradosPinza;
        }
        modo = CERRAR;
      }

    }
    else if ( X < 300) {
      if ( gradosPinza > GMIN) {
        gradosPinza = gradosPinza - 3;
        moviendo = 3;
        if (grabando == 1 && modo != ABRIR) {
          modoAnterior = modo;
          grabar();
          tiempoInicial = gradosPinza;
        }
        modo = ABRIR;
      }
    }
    else {
      moviendo = 0;
      if (grabando == 1 && modo != PARADA) {
        modoAnterior = modo;
        grabar();
        tiempoInicial = gradosPinza;
      }
      modo = PARADA;
    }

    // Mover
    servoP.write(gradosPinza);
    //Serial.println("G: " + String(gradosPinza));

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
        servoY.write(90);
        delay(tiempo[j]);
      }
      else if (posicion[j] == ARRIBA) {
        servoY.write(0);
        delay(tiempo[j]);
      }
      else if (posicion[j] == ABAJO) {
        servoY.write(180);
        delay(tiempo[j]);
      }
      else if (posicion[j] == ABRIR) {
        do{
          Serial.println("gp: " + String(gradosPinza));
          gradosPinza = gradosPinza - 3;
          Serial.println("gp: " + String(gradosPinza));
          servoP.write(gradosPinza);
        }
        while(gradosPinza >= tiempo[j]  && gradosPinza <= GMAX);
      }
      else if (posicion[j] == CERRAR) {
        do{
          Serial.println("gp: " + String(gradosPinza) + " obj: " + String(tiempo[j]));
          gradosPinza = gradosPinza + 3;
          Serial.println("gp: " + String(gradosPinza));
          servoP.write(gradosPinza);
        }
        while(gradosPinza <= tiempo[j] && gradosPinza >= GMIN);
      }
    }
    reproduciendo = 0;
  }

}

void grabar() {
  int tiempoFin;
  if(modoAnterior == 5 || modoAnterior == 6){
    tiempoFin = tiempoInicial;
  }
  else{
    tiempoFin = millis() - tiempoInicial;
  }
  posicion[i] = modoAnterior;
  tiempo[i] = tiempoFin;
  Serial.println("tiempoInicial: " + String(tiempoInicial) + ", tiempoFin:" + String(tiempoFin) + " tiempo[i]:" + String(tiempo[i]) + ", posicion[i]: " + String(posicion[i]));
  i++;
}

void irA0() {
  servoX.write(0);
  while (digitalRead(Xder) == HIGH) { }
  servoX.write(90);

  servoY.write(0);
  while (digitalRead(Yab) == HIGH) {  }
  servoY.write(90);

  while(gradosPinza > GMIN) {
    gradosPinza = gradosPinza - 3;
    servoP.write(gradosPinza);
  }
}

