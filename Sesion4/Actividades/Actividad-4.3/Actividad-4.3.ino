#include <Servo.h>

#define boton_pin 13 // pin digital para el botón
#define X_pin A0 // pin analógico para leer eje X

Servo servo;
int pinServo = 2;

int pinDer = 8;
int pinIzq = 7;

int modo = 0;

int tiempoCm = 0;
int tiempoIda = 0;

int cm_ = 0;
int cm = 0;
int actual = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(pinServo);
  pinMode(boton_pin, INPUT_PULLUP);

  pinMode(pinDer, INPUT);
  pinMode(pinIzq, INPUT);

}

void loop() {

  if(modo == 0){
      servo.write(180);
      modo = 1;
  }
  
  if(modo == 1){

    int der = digitalRead(pinDer);
    int izq = digitalRead(pinIzq);
    Serial.println("Der " + String(der));
    Serial.println("Izq " + String(izq));
    
    if(der == LOW && tiempoIda != 0){
      servo.write(90);
      tiempoCm = (millis()-tiempoIda)/24;
      Serial.println("TiempoCm " + String(tiempoCm));
      modo = 2;  
    }
    else if(izq == LOW){
      tiempoIda = millis();
      Serial.println("tiempoIda " + String(tiempoIda));
      servo.write(0);
    }
    
  }
  if(modo == 2){

    // 10-1000,20-1000,10-400,0-1500
    // 20-1000,21-500,1-1000
    // 5-100,0-100
    
    Serial.println("Coordenadas: "); 
    while (Serial.available() == 0) { }

    int cm_  = Serial.readStringUntil('-').toInt();
    int tiempo  = Serial.readStringUntil(',').toInt();

    Serial.println(String(cm_) + ", " + String(tiempo) + ", " + actual);

    if(actual > cm_){
      cm = actual - cm_;
      servo.write(0);
    }
    else if(cm_ >= actual){
      cm = cm_- actual;
      servo.write(180);
    }
    

    actual = cm_;
    Serial.println(String(actual) + ", " + String(tiempoCm*cm));

    delay(tiempoCm*cm);
    servo.write(90);
    delay(tiempo);

    
    if(Serial.available() == 0){
      actual = 0;
      int der = digitalRead(pinDer);
      Serial.println("Der " + String(der));
      servo.write(0);
      while (der == HIGH) { der = digitalRead(pinDer); }
      servo.write(90);
    }
    
  }

}
