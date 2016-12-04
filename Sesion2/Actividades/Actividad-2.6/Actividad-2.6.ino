#include <Servo.h>
#include <Keypad.h>

const byte nfilas = 4;
const byte ncolumnas = 4;
char teclas[nfilas][ncolumnas] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};

byte pfilas[nfilas] = {A0,A1,A2,A3};   // Filas
byte pcolumnas[ncolumnas] = {7,6,5,4}; //Columnas
Keypad teclado = Keypad( makeKeymap(teclas), pfilas, pcolumnas, nfilas, ncolumnas );


Servo servo1;
int pinServo1 = 8;

long distancia;
long tiempoRespuesta;

int pinTrig = 13;
int pinEcho = 12;

long tiempoCalculado;

int estado = 0;
int distanciaApertura = 3;

int pinLuz = A5;
int valorMinLuz = 100;

int personas = 0;

int pinledR = 9;
int pinledG = 10;
int pinledB = 11;

String bufferLectura = "";
int modoLectura = 0;
int cambio = 0;

int tiempo = 5000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinTrig, OUTPUT); 
  pinMode(pinEcho, INPUT);

  pinMode(pinledR, OUTPUT); 
  pinMode(pinledG, OUTPUT); 
  pinMode(pinledB, OUTPUT); 
  
  servo1.attach(pinServo1);
  servo1.write(0);
  Serial.println("Setup()");

}


void semaforoVerde(){
    digitalWrite(pinledG, HIGH);
    digitalWrite(pinledR, LOW);
    digitalWrite(pinledB, LOW);
}

void semaforoRojo(){
    digitalWrite(pinledG, LOW);
    digitalWrite(pinledR, HIGH);
    digitalWrite(pinledB, LOW);
}

void semaforoAzul(){
    digitalWrite(pinledG, LOW);
    digitalWrite(pinledR, LOW);
    digitalWrite(pinledB, HIGH);
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

  char tecla = teclado.getKey();
  if (tecla != '\0'){
    Serial.println("tecla pulsada: "+String(tecla));

    cambio = 1;

     if(modoLectura == 1 && tecla != '*'){
        bufferLectura = bufferLectura + tecla;
        Serial.println("buffer: "+bufferLectura);  
     }

     if(modoLectura == 1 && tecla == '*'){
        tiempo = bufferLectura.toInt()*1000; 
        Serial.println("tiempo: "+String(tiempo));  
        bufferLectura = "";
        modoLectura = 0;
        cambio = 0;
        Serial.println("Modo 0"); 
     }
     
      if(tecla == '*' && modoLectura == 0 && cambio == 1){
        modoLectura = 1;
        Serial.println("Modo 1");
     }
  }

  
  if(millis() - tiempoCalculado > 1000 && estado == 0 ){
            semaforoVerde();
  
    Serial.println("\tValor luz" + String(valorLuz));
    if(distancia <= distanciaApertura){
        semaforoRojo();

      servo1.write(180);
      tiempoCalculado = millis();
      estado = 1;
    }

    if(valorLuz < valorMinLuz){
        semaforoAzul();

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
      semaforoVerde();

  }

  if(estado == 2 && distancia <= distanciaApertura){
      servo1.write(0);
      tiempoCalculado = millis();
      estado = 0;
      personas++;
      semaforoVerde();
  }

  if(millis() - tiempoCalculado > tiempo && (estado == 1 || estado == 2)){
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
          semaforoVerde();

  }  

}
