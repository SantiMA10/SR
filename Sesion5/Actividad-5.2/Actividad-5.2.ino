#include <Servo.h>

#define boton_pin 13 // pin digital para el botón
#define Y_pinY A0 // pin analógico para leer eje X
#define X_pinX A1 // pin analógico para leer eje X

#define Y_pinP A2 // pin analógico para leer eje X
#define X_pinP A3 // pin analógico para leer eje X

Servo servoX;
int pinServoX = 5;

Servo servoY;
int pinServoY = 3;

// Grados pinza, MAX y MIN admitido
#define GMAX 110
#define GMIN 10


Servo servoP;
int pinServoPinza = 6;
int gradosPinza = GMIN;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoX.attach(pinServoX);
  servoY.attach(pinServoY);
  pinMode(boton_pin, INPUT_PULLUP);

  servoP.attach(pinServoPinza);
  servoP.write(gradosPinza);

}

void loop() {
  // put your main code here, to run repeatedly:
  int valorX = analogRead(X_pinX);
  //Serial.println("X: "+String(valorX));

  if(valorX < 412){
    servoX.write(180);
  }
  else if(valorX > 412 && valorX < 612){
    servoX.write(90);
  }
  else if(valorX > 612){
    servoX.write(0);
  }

  int valorY = analogRead(Y_pinY);
  //Serial.println("Y: "+String(valorY));

  if(valorY < 412){
    servoY.write(0);
  }
  else if(valorY > 412 && valorY < 612){
    servoY.write(90);
  }
  else if(valorY > 612){
    servoY.write(180);
  }

   int X = analogRead(X_pinP);
  //Serial.println("P: "+String(X));

  // Aumentar / reducir grados segun X-Joystick
  // Joystick de 0 a 1024, desechamos las posiciones centrales
  if(X > 700 ){
      if ( gradosPinza < GMAX)
         gradosPinza = gradosPinza+3;
  } else if ( X < 300){
      if ( gradosPinza > GMIN)
        gradosPinza = gradosPinza-3;
  } 
  
  // Mover
  servoP.write(gradosPinza);
  Serial.println("G: "+String(gradosPinza));
  
}
