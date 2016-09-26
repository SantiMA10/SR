
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int valorLuz = analogRead(A2);
  Serial.println("Valor: "+String(valorLuz));
  
  if ( valorLuz < 200){
    digitalWrite(13, HIGH); 
  } else {
    digitalWrite(13, LOW);
  }

}
