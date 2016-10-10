#include <Servo.h>

#define boton_pin 13 // pin digital para el botón
#define X_pin A0 // pin analógico para leer eje X

Servo servo;
int pinServo = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(pinServo);
  pinMode(boton_pin, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  int valorX = analogRead(X_pin);
  Serial.println("X: "+String(valorX));

  if(valorX < 100){
    servo.write(180);
  }
  else if(valorX > 100 && valorX < 412){
    servo.write(100);
  }
  else if(valorX > 412 && valorX < 612){
    servo.write(90);
  }
  else if(valorX > 612 && valorX < 923){
    servo.write(75);
  }
  else if(valorX > 923){
    servo.write(0);
  }
  
}
