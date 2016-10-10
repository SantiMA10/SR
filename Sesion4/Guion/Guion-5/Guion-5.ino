String cadena;   
int entero;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);     
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Nombre: "); 
  while (Serial.available() == 0) { }  // Esperar mientras no haya nada    
  
  cadena = Serial.readString();  
  Serial.println("Es "+ cadena);
  
  Serial.println("Edad: ");
  while (Serial.available() == 0)  {}

  entero = Serial.parseInt();   // pasar a entero
  Serial.println("Es "+ String(entero));

}
