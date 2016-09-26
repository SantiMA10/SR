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

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  servo1.attach(8);
  Serial.println("Setup()");

}

void loop() {
  // put your main code here, to run repeatedly:
  char tecla = teclado.getKey();
  if (tecla != '\0'){
    Serial.println("tecla pulsada: "+String(tecla));

        if ( tecla != '#'){
          bufferLectura = bufferLectura + tecla;
          Serial.println("buffer: "+bufferLectura);
        } else { // es # transformamos a entero
          int valorNumerico = bufferLectura.toInt();
          Serial.println("Aceptado: "+String(valorNumerico));
          servo1.write(valorNumerico);
          bufferLectura = ""; // reinicio
        }
  }

}
