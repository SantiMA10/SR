int valorPotenciometro;
int valorSalidaAnalogica;



void setup() {
  Serial.begin(9600); // Iniciar el Serial
  Serial.println("Setup");

 // Los pins digitales se declaran - LED
  pinMode(5, OUTPUT); // Salida

}

void loop() {
  // put your main code here, to run repeatedly:
   // Leemos el valor del pin A0 - Potenciometro
   valorPotenciometro = analogRead(A0); // 0 - 1024
   Serial.println("valor: "+String(valorPotenciometro));
  
   // Transformar de 0 a 1023 -> 0 a 255
   valorSalidaAnalogica = map(valorPotenciometro, 0, 1023, 0, 255);
   // Escribimos en valor en el pin 5 - LED
   analogWrite(5,valorSalidaAnalogica);

}
