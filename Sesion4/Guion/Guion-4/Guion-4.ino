char datoLeido;

void setup(){
   Serial.begin(9600);
   Serial.println("Setup()");
}

void loop()
{
  while(Serial.available() > 0) // Nº de datos disponibles para leer.
  {
      datoLeido = Serial.read(); // Leer
      Serial.println(datoLeido);

  }
}

