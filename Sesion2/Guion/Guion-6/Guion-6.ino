int pinRojo = 9;
int pinVerde = 10;
int pinAzul = 11;


void setup() {
  pinMode(pinRojo, OUTPUT);
   pinMode(pinVerde, OUTPUT);
   pinMode(pinAzul, OUTPUT);


}

void loop() {
  digitalWrite(pinRojo,HIGH);
  digitalWrite(pinVerde,LOW);
  digitalWrite(pinAzul,LOW);
  delay(500);
  digitalWrite(pinRojo,LOW);
  digitalWrite(pinVerde,HIGH);
  digitalWrite(pinAzul,LOW);
  delay(500);


}
