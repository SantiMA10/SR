#include <Servo.h>

Servo servo;
int pin = 2;

void setup() {
  Serial.begin(9600);
  servo.attach(pin);
}

void loop() {
  Serial.println("Enviar: giro en sentido 1");
  servo.write(0);
  delay(2000);

  Serial.println("Enviar: detener");
  servo.write(90);
  delay(2000);

  Serial.println("Enviar: giro en sentido 2");
  servo.write(180);
  delay(2000);
}
