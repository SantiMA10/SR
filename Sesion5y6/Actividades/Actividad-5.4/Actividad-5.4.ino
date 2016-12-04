#include <Servo.h>

#define boton_pin 13 // pin digital para el botón
#define X_pin A0 // pin analógico para leer eje X
#define Y_pin A1 // pin analógico para leer eje Y

#define LIMITE_CERCA_X_PRESSED 0
#define LIMITE_LEJOS_X_PRESSED 0
#define LIMITE_CERCA_Y_PRESSED 0
#define LIMITE_LEJOS_Y_PRESSED 0

// Grados pinza, MAX y MIN admitido
#define GMAX 110
#define GMIN 10

#define AGARRE_PINZA 112

Servo servoX;
Servo servoY;
Servo servoP;

//GRANDE 82
//GRANDE 112

int limiteLejosX = 13;

int limiteCercaX = 8;
int limiteLejosY = 11;
int limiteCercaY = 7;


double tiempoCentimetroX = 0;
double tiempoCentimetroY = 0;

double posicionX = 0;
double posicionY = 0;

void setup() {
  // inicializar pin 2 (Entrada)
  pinMode(boton_pin, INPUT_PULLUP);
  Serial.begin(9600);
  servoX.attach(5);
  servoY.attach(3);
  servoP.attach(6);
  servoP.write(GMIN);

  pinMode(limiteLejosX, INPUT);
  pinMode(limiteCercaX, INPUT);
  pinMode(limiteLejosY, INPUT);
  pinMode(limiteCercaY, INPUT);

  calibrarX();
  calibrarY();

  //ir inicio
  irACentimetroX(0);
  irACentimetroY(5);

  //agarrar primer cubo
  irACentimetroX(0);
  servoP.write(GMIN);
  irACentimetroY(24);
  delay(750);
  servoP.write(AGARRE_PINZA);
  delay(500);
  irACentimetroY(15);

  //soltar primer cubo
  irACentimetroX(20);
  irACentimetroY(24);
  delay(750);
  servoP.write(GMIN);
  delay(500);
  irACentimetroY(15);

  //agarrar segundo cubo
  irACentimetroX(10);
  irACentimetroY(24);
  delay(750);
  servoP.write(AGARRE_PINZA);
  delay(500);
  irACentimetroY(15);

  //soltar segundo cubo
  irACentimetroX(20);
  irACentimetroY(22);
  delay(750);
  servoP.write(GMIN);
  delay(500);
}
 
void loop() {
  
}

void calibrarX(){
  unsigned long tiempoInicio = 0;
  unsigned long tiempoTotal = 0;
  servoX.write(0);
  while(true){
    if(LIMITE_CERCA_X_PRESSED == digitalRead(limiteCercaX))
      break;
  }
  servoX.write(180);
  tiempoInicio = millis();
  while(true){
     if(LIMITE_LEJOS_X_PRESSED == digitalRead(limiteLejosX))
        break;
  }
  servoX.write(90);
  tiempoTotal = millis() - tiempoInicio;
  tiempoCentimetroX = tiempoTotal/24;
}


void calibrarY(){
  unsigned long tiempoInicio = 0;
  unsigned long tiempoTotal = 0;
  servoY.write(0);
  while(true){
    if(LIMITE_CERCA_Y_PRESSED == digitalRead(limiteCercaY))
      break;
  }
  servoY.write(180);
  tiempoInicio = millis();
  while(true){
     if(LIMITE_LEJOS_Y_PRESSED == digitalRead(limiteLejosY))
        break;
  }
  servoY.write(90);
  tiempoTotal = millis() - tiempoInicio;
  tiempoCentimetroY = tiempoTotal/24;
}



void irACentimetroX(double centimetro){
  double distancia = centimetro - posicionX;

  if(distancia>0){
    servoX.write(0);
    delay(distancia*tiempoCentimetroX);
    servoX.write(90);
  }else if(distancia<0){
    servoX.write(180);
    delay(abs(distancia)*tiempoCentimetroX);
    servoX.write(90);
  }
  posicionX=centimetro;
}

void irACentimetroY(double centimetro){
  double distancia = centimetro - posicionY;

  if(distancia>0){
    servoY.write(0);
    delay(distancia*tiempoCentimetroY);
    servoY.write(90);
  }else if(distancia<0){
    servoY.write(180);
    delay(abs(distancia)*tiempoCentimetroY);
    servoY.write(90);
  }
  posicionY=centimetro;
}


