int pinsensor = 3;
int pinluz = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(pinsensor, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int pirValor = digitalRead(pinsensor);
  Serial.println("Valor: "+String(pirValor));
  
  if(pirValor == HIGH){
    Serial.println("Detectado movimiento");
    digitalWrite(pinluz, HIGH);
  } else {
    Serial.println("- - - -");
    digitalWrite(pinluz, LOW);
  }
  
  delay(50);
}
