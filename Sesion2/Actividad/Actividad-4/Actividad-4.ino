#include <Servo.h>

Servo servo1;

long distancia;
long tiempoRespuesta;

int pinTrig = 5;
int pinEcho = 4;

long tiempoCalculado;

int estado = 0;
int distanciaApertura = 3;

int calcularDistancia(){

  digitalWrite(pinTrig,LOW); /* Por seguridad volvemos a poner el Trig
  a LOW*/
  delayMicroseconds(5);
  
  digitalWrite(pinTrig, HIGH); /* Emitimos el pulso ultrasónico */
  delayMicroseconds(10);
  
  tiempoRespuesta = pulseIn(pinEcho, HIGH); /* Medimos la longitud del
  pulso entrante Cuanto tiempo tarda la entrada en pasar de HIGH a LOW 
  retorna microsegundos */
  Serial.println("Tiempo "+ String(tiempoRespuesta)+" microsegundos");
  
  distancia= int(0.017*tiempoRespuesta);
  Serial.println("Distancia "+ String(distancia)+"cm");

  return distancia;
  
}

void comprobarPresencia(){
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinTrig , OUTPUT); /* trig envía el pulso ultrasónico */
  pinMode(pinEcho, INPUT);
  servo1.attach(8);
  servo1.write(0);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(estado == 0){
    int distancia = calcularDistancia();
    if(distancia <= distanciaApertura){
      servo1.write(180);
      tiempoCalculado = millis();
      estado = 1;
    }
  }

  if(millis() - tiempoCalculado > 5000 && estado == 1){

    distancia = calcularDistancia();
    if(distancia > distanciaApertura){
      servo1.write(0);
      estado = 0;
    }
    else{
      tiempoCalculado = millis();
    }
    
  }  
  

}
