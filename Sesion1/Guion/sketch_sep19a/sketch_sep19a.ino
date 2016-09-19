// Pins
int led1 = 2;
int led2 = 3;
int boton = 4;
int estadoBoton = 0;
// 0: todo apagado
// 1: led1 encendido
// 2: led2 encendido
int usuarioPulsa = 0;

void setup() {
 Serial.begin(9600); // Iniciar el Serial
 Serial.println("Setup");

 // Inicializamos los pins digitales como salida
 // Queremos que alimenten electrimanete los leds
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
 // Queremos leer la entrada
 pinMode(boton, INPUT);
}
// the loop function runs over and over again forever
void loop() {
 int lectura = digitalRead(boton);

 if( lectura == HIGH && usuarioPulsa == 0){
   Serial.println("VALOR HIGH");
    usuarioPulsa = 1;
   if( estadoBoton == 2){
   estadoBoton = 0;
   } else {
   estadoBoton++;
   }
  
   switch(estadoBoton){
     case 0:
     digitalWrite(led1, LOW);
     digitalWrite(led2, LOW);
     break;
     case 1:
     digitalWrite(led1, HIGH);
     digitalWrite(led2, LOW);
     break;
     case 2:
     digitalWrite(led1, LOW);
     digitalWrite(led2, HIGH);
     break;
   }
  delay(1000);
 } else if ( lectura == LOW && usuarioPulsa == 1){
   Serial.println("VALOR LOW");
   usuarioPulsa = 0;
 }
 
}
