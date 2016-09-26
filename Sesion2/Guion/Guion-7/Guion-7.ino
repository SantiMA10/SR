int pinRojo = 9;
int pinVerde = 10;
int pinAzul = 11;

int gradoColor = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(pinRojo, OUTPUT);
   pinMode(pinVerde, OUTPUT);
   pinMode(pinAzul, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(pinRojo, 255 - gradoColor);
  analogWrite(pinAzul,gradoColor);
  analogWrite(pinVerde,0);
  delay(15);
  
  gradoColor++;
  if ( gradoColor > 255)
    gradoColor = 0;

}
