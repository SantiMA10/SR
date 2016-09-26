#include <Servo.h>

Servo servo1;
int delay_time = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  servo1.attach(8);


}

void loop() {
  // put your main code here, to run repeatedly:
  servo1.write(180);
  Serial.println("180");
  delay(delay_time);
  servo1.write(90);
  Serial.println("90");
  delay(delay_time);
  servo1.write(0);
  Serial.println("0");
  delay(delay_time);

}
