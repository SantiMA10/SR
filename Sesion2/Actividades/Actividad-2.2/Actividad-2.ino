#include <Keypad.h>
#include <Servo.h>

Servo servo1;

const byte nfilas = 4;
const byte ncolumnas = 4;
char teclas[nfilas][ncolumnas] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};

byte pfilas[nfilas] = {2,3,4,5};  // Filas
byte pcolumnas[ncolumnas] = {A0,A1,A2,A3}; //Columnas
Keypad teclado = Keypad( makeKeymap(teclas), pfilas, pcolumnas, nfilas, ncolumnas );

String bufferLectura = "";

long inicioTiempo;
long tiempoPuertaAbierta = 5000;
int ignorar = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  servo1.attach(8);
  Serial.println("Setup()");

  servo1.write(0);


}

void loop() {
  // put your main code here, to run repeatedly:
  char tecla = teclado.getKey();
  if (tecla != '\0'){
    Serial.println("tecla pulsada: "+String(tecla));

        if ( tecla == 'A' && ignorar == 0){
          inicioTiempo = millis();
          servo1.write(180);
          ignorar = 1;
        } 
        else if(tecla == 'C' && ignorar == 1){
          ignorar = 0;
          servo1.write(0);
        }
  }

  if(millis() - inicioTiempo >= tiempoPuertaAbierta && ignorar == 1){
    servo1.write(0);
    ignorar = 0;
  }

}
