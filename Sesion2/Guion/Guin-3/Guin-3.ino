long distancia;
long tiempoRespuesta;

int pinTrig = 9;
int pinEcho = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinTrig , OUTPUT); /* trig envía el pulso ultrasónico */
  pinMode(pinEcho, INPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(pinTrig,LOW); /* Por seguridad volvemos a poner el Trig
  a LOW*/
  delayMicroseconds(5);
  
  digitalWrite(pinTrig, HIGH); /* Emitimos el pulso ultrasónico */
  delayMicroseconds(10);
  
  tiempoRespuesta = pulseIn(pinEcho, HIGH); /* Medimos la longitud del
  pulso entrante Cuanto tiempo tarda la entrada en pasar de HIGH a LOW 
  retorna microsegundos */
  Serial.println("Tiempo "+ String(tiempoRespuesta)+" microsegundos");
  
  distancia= int(0.017*tiempoRespuesta); /* Calcular la distancia
  conociendo la velocidad */

  Serial.println("Distancia "+ String(distancia)+"cm");
  delay(1000);

}
