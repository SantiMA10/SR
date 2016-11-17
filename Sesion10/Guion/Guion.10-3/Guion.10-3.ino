#include <Servo.h>

Servo servoIzq;
Servo servoDer;

int pinServoIzq = 8;
int pinServoDer = 9;

void setup()
{
  servoIzq.attach(pinServoIzq);
  servoDer.attach(pinServoDer);
}

void loop()
{
  servoIzq.write(180); 
  servoDer.write(180);
  delay(1000);
  servoIzq.write(90); 
  servoDer.write(90);
  delay(3000);
  servoIzq.write(0); 
  servoDer.write(0);
  delay(1000);
  servoIzq.write(90); 
  servoDer.write(90);
  delay(3000);
}

