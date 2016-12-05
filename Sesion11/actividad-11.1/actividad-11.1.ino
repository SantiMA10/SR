#include <Servo.h>
//#include <LiquidCrystal_I2C.h> 

int LINEA = 1;
int NO_LINEA = 0;

Servo servoI;
Servo servoD;

//LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Pines: sensores de izquierda a derecha 1 2 3 4
int pinSensor2 = 2;
int pinSensor3 = 3;

// Valores
int Sensor2 = -1;
int Sensor3 = -1;

int modo = 0;
int giro = 0;
int modoGiro = 0;

long tiempoAvance = 0,
     tiempoMaxAvance = 5000;

void setup() {
  Serial.begin(9600);
  servoI.attach(8);
  servoD.attach(9);

  pinMode( pinSensor2 , INPUT);
  pinMode( pinSensor3 , INPUT);
  
  //lcd.begin(20,4); 
  //lcd.setCursor(0,0);
  //lcd.print("+++++>FSOCIETY<+++++");

  tiempoAvance = millis();

}

void avanzar() {
  servoD.write(180);
  servoI.write(0);
}


void darMediaVueltaOfensivo() {

  servoD.write(180);
  servoI.write(180);

  int carrilEncontrado = 0;
  float aux = 0.01;
  while (carrilEncontrado < 300) {
    Sensor2 = digitalRead(pinSensor2);
    Sensor3 = digitalRead(pinSensor3);

    if ( Sensor2 == NO_LINEA && Sensor3 == NO_LINEA ) {
      aux = aux + 0.05;
      carrilEncontrado = carrilEncontrado + aux;
      Serial.println(String(carrilEncontrado));
    }
  }
  tiempoAvance = millis();
}

void darMediaVueltaDefensivo() {

  servoD.write(180);
  servoI.write(180);

  boolean carrilEncontrado = false;
  while (!carrilEncontrado) {
    Sensor2 = digitalRead(pinSensor2);
    Sensor3 = digitalRead(pinSensor3);

    if ( Sensor2 == NO_LINEA && Sensor3 == NO_LINEA ) {
      carrilEncontrado = true;
    }
  }

  tiempoAvance = millis();
}


int sensores[] = { -1, -1};

void actualizarTodosLosSensores() {

  Sensor2 = digitalRead(pinSensor2);
  Sensor3 = digitalRead(pinSensor3);

}

void loop() {

  actualizarTodosLosSensores();

  if (Sensor2 == LINEA && Sensor3 == LINEA) {
    if (modo == 0) {
      modo = 1;
      darMediaVueltaOfensivo();
    }
    else {
      modo = 0;
      darMediaVueltaDefensivo();
    }
  }
  else {
    avanzar();
  }

}
