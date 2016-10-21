#include <Servo.h>

#define boton_pin 13 // pin digital para el botón
#define Y_pinY A0 // pin analógico para leer eje X
#define X_pinX A1 // pin analógico para leer eje X

#define DERECHA 0
#define IZQUIERDA 1
#define PARADA 2

#define sizearray 5

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

void setup() {
  Serial.begin(9600);
  servoX.attach(pinServoX);

  pinMode(Xder, INPUT);

  modo = PARADA;
  grabando = 0;
  reproduciendo = 0;
  i = 0;
}

void loop() {
  int valorX = analogRead(X_pinX);
  Serial.println("X: "+String(valorX));

  if(valorX < 412){
    servoX.write(180);
    
    grabar();
    modoAnterior = modo;
    modo = IZQUIERDA;
    tiempoInicial = millis();
  }
  else if(valorX > 412 && valorX < 612){
    servoX.write(90);
    
    grabar();
    modoAnterior = modo;
    modo = PARADA;
    tiempoInicial = millis();
  }
  else if(valorX > 612){
    servoX.write(0);
    
    grabar();
    modoAnterior = modo;
    modo = DERECHA;
    tiempoInicial = millis();
  }

  if(Serial.available() != 0){
    
    if(Serial.readString() == "g"){
      Serial.println("Grabando");
      grabando = 1;
      reproduciendo = 0;
      i = 0;
      irA0();
    }
  
    if(Serial.readString() == "r"){
      Serial.println("Reproduciendo");
      grabando = 0;
      reproduciendo = 1;
      i = 0;
      irA0();
    }
    
  }

  if(reproduciendo == 1){
    Serial.println("reproducion");
    int j;
    for(j = 0; j < sizeof(posicion)/sizeof(int); j++){
      if(posicion[i] == DERECHA){
        servoX.write(0);
        delay(tiempo[i]);
      }
      else if(posicion[i] == IZQUIERDA){
        servoX.write(180);
        delay(tiempo[i]);
      }
      else if(posicion[i] == PARADA){
        servoX.write(90);
        delay(tiempo[i]);
      }
    }
  }

}

void grabar(){
  if(modo != modoAnterior && grabando == 1){
    int tiempoFin = millis() - tiempoInicial;
    posicion[i] = modo;
    tiempo[i] = tiempoFin;
    i++;
  }
}

void irA0(){
  servoX.write(0);
  while(digitalRead(Xder) == HIGH) { Serial.println("Xder:" + String(digitalRead(Xder))); }
  servoX.write(90);
}

