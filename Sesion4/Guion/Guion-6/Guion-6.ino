String comando;   
int pin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Pin 13 como salida
  pinMode(pin, OUTPUT);  


}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0) { }  // Esperar ...
  
  comando = Serial.readString(); 
  
  if(comando.equals("encender")) {
    Serial.println("encendido");
    digitalWrite(pin, HIGH); 

  } else if (comando.equals("apagar")) {
    Serial.println("apagado");
    digitalWrite(pin, LOW);
  }

}
