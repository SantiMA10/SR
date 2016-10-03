#include <Servo.h>
#include <TM1637.h>

int pinClk = 3;
int pinDio = 2;

TM1637 pantalla(pinClk,pinDio);


Servo servo1;

long distancia;
long tiempoRespuesta;

int pinTrig = 5;
int pinEcho = 4;

long tiempoCalculado;

int estado = 0;
int distanciaApertura = 3;

int pinLuz = A2;
int valorMinLuz = 100;

int personas = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinTrig , OUTPUT); /* trig envía el pulso ultrasónico */
  pinMode(pinEcho, INPUT);
  servo1.attach(8);
  servo1.write(0);

  pantalla.init();
  pantalla.set(BRIGHT_TYPICAL);

}

void imprimir(int numero){
  int digito0 = numero/1000;    
  Serial.println("digito0 "+ String(digito0)); 

  int digito1 = (numero - digito0*1000)/100; 
  Serial.println("digito1 "+ String(digito1));

  int digito2 = (numero - (digito0*1000 + digito1*100))/10;  
  Serial.println("digito2 "+ String(digito2));

  int digito3 = numero - (digito0*1000 + digito1*100 + digito2*10);
  Serial.println("digito3 "+ String(digito3));
  
  pantalla.display(0,digito0);
  pantalla.display(1,digito1);
  pantalla.display(2,digito2);
  pantalla.display(3,digito3);

}

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

void loop() {
  // put your main code here, to run repeatedly:

  int valorLuz = analogRead(pinLuz);
  int distancia = calcularDistancia();
  imprimir(personas);
  
  if(millis() - tiempoCalculado > 1000 && estado == 0 ){
   
    Serial.println("\tValor luz" + String(valorLuz));
    if(distancia <= distanciaApertura){
      servo1.write(180);
      tiempoCalculado = millis();
      estado = 1;
    }

    if(valorLuz < valorMinLuz){
      servo1.write(180);
      tiempoCalculado = millis();
      estado = 2;
    }
  }

  if(estado == 1 && valorLuz < valorMinLuz){
      servo1.write(0);
      tiempoCalculado = millis();
      estado = 0;
      personas++;
  }

  if(estado == 2 && distancia <= distanciaApertura){
      servo1.write(0);
      tiempoCalculado = millis();
      estado = 0;
      personas++;
  }

  if(millis() - tiempoCalculado > 5000 && (estado == 1 || estado == 2)){
      Serial.println("\tValor luz" + String(valorLuz));

    distancia = calcularDistancia();
    if(distancia > distanciaApertura){
      servo1.write(0);
      estado = 0;
      personas++;
    }
    else{
      tiempoCalculado = millis();
    }
    
  }  
  

}
