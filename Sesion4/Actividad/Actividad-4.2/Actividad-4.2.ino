#include <Servo.h>

#define boton_pin 13 // pin digital para el botón
#define X_pin A0 // pin analógico para leer eje X

Servo servo;
int pinServo = 2;

int modo = 0;

int pinDer = 8;
int pinIzq = 7;

int pulsado = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(pinServo);
  pinMode(boton_pin, INPUT_PULLUP);

  pinMode(pinDer, INPUT);
  pinMode(pinIzq, INPUT);

}

void loop() {

  int boton = digitalRead(boton_pin);
  Serial.println("Modo " + String(modo));

  if(boton == LOW && pulsado == 0){
    if(modo == 0){
      servo.write(0);
      modo = 1;
    }
    else if(modo == 1){
      modo = 0;
    }
    pulsado = 1;
  }

  if(boton == HIGH && pulsado == 1){
    pulsado = 0;
  }
  
  // put your main code here, to run repeatedly:
  if(modo == 0){
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
  else if(modo == 1){
    int der = digitalRead(pinDer);
    int izq = digitalRead(pinIzq);
    Serial.println("Der " + String(der));
    Serial.println("Izq " + String(izq));
    
    
    if(der == LOW){
      servo.write(180);
    }
    else if(izq == LOW){
      servo.write(0);
    }
    
  }
  
}
