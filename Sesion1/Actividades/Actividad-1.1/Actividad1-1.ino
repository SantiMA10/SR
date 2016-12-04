//Santiago Martin Agra
//Sergio Moradas Quintana

int led1 = 2;
int led2 = 3;
int led3 = 4;

int boton = 8;
int pulsado = 0;

void setup() {
  Serial.begin(9600); // Iniciar el Serial
  Serial.println("Setup");
 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(boton, INPUT);

}

void loop() {

  int lectura = digitalRead(boton);
  
  if(lectura == HIGH && pulsado == 0){
    pulsado = 1;

    int r = random(0, 3);
    Serial.println("r:");

    switch(r){
      case 0:
        Serial.println("Encendidos: 1");
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
      break;
      case 1:
        Serial.println("Encendidos: 2");
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
      break;
      case 2:
        Serial.println("Encendidos: 3");
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
      break;
    }
    
  }
  else if(lectura == LOW){
    pulsado = 0;
  }
  

}
