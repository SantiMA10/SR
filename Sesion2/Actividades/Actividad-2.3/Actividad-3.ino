#include <Keypad.h>
#include <Servo.h>

Servo servo1;
int pinled = 13;

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

char password[] = {'5', '4', '1', '2'};
char password_in[4];
int in = 0;

int correcto = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  servo1.attach(8);
  Serial.println("Setup()");

  pinMode(pinled, OUTPUT);

  servo1.write(0);


}

void parpadeo(){
    digitalWrite(pinled, HIGH);
    delay(500);
    digitalWrite(pinled, LOW);
    delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  char tecla = teclado.getKey();
  
  if (tecla != '\0' && in < 4){
    Serial.println("tecla pulsada: "+String(tecla));
    password_in[in] = tecla;
    in++;
     
  }

  if(in == 4){
    int i;
    for(i = 0; i < 4; i++){
      Serial.println(String(password[i]) + "!=" + String(password_in[i]));
      if(password[i] != password_in[i]){
        correcto = 1;
      }
    }
    if(correcto == 0){
      servo1.write(180);
      digitalWrite(pinled, HIGH);
      delay(1000);
      digitalWrite(pinled, LOW);
      servo1.write(0);
      in = 0;
    }
    else if(correcto == 1){
      parpadeo();
      parpadeo();
      parpadeo();
      correcto = 0;
      in = 0;
    }
  }

}
