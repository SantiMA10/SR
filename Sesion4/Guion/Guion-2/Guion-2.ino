#define boton_pin 13 // pin digital para el botón
#define X_pin A0 // pin analógico para leer eje X
#define Y_pin A1 // pin analógico para leer eje Y

void setup() {
  // inicializar pin 2 (Entrada)
  pinMode(boton_pin, INPUT_PULLUP);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Boton pulsado: "+String(digitalRead(boton_pin)));

  int valorX = analogRead(X_pin);
  Serial.println("X: "+String(valorX));

  int valorY = analogRead(Y_pin);
  Serial.println("Y: "+String(valorY));

  delay(100);

}
