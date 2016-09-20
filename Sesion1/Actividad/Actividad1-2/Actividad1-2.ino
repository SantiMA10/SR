int led1 = 2;
int led2 = 3;

int boton1 = 5;
int boton2 = 4;

int colores[10];
int nivel = 2;
int pulsacion = 0;
int pulsando = 0;

int modo = 0;

void setup() {
  Serial.begin(9600); // Iniciar el Serial
  Serial.println("Setup");

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);

  int i;
  for(i = 0; i < sizeof(colores)/sizeof(int); i++){
    colores[i] = random(0,2);
    Serial.print(", " + String(colores[i]));
  }
  Serial.println();

}

void loop() {

  if(modo == 0){
    
    int i;
    Serial.println("colores");
    for(i = 0; i < nivel; i++){
      if(colores[i] == 0){
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
      }
      else if(colores[i] == 1){
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
      }
      delay(1000);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      delay(500);
    }

    modo = 1;
  }
  else if(modo == 1){

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    int pulsacion_boton1 = digitalRead(boton1);
    int pulsacion_boton2 = digitalRead(boton2);
    
    if(pulsacion_boton1 == LOW && pulsacion_boton2 == HIGH && pulsando == 0){
      pulsando = 1;
      if(colores[pulsacion] == 0){
        pulsacion++;
      }
      else{
        nivel = 2;
        modo = 0;
        pulsacion = 0;
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        delay(1000);
      }
      
    
      Serial.println("Nivel :" + String(nivel));
      Serial.println("Pulsacion :" + String(pulsacion));
      Serial.println("boton 0: " + String(pulsando));
    }
    else if(pulsacion_boton2 == LOW && pulsacion_boton1 == HIGH && pulsando == 0){
      pulsando = 1;
      if(colores[pulsacion] == 1){
        pulsacion++;
      }
      else{
        nivel = 2;
        modo = 0;
        pulsacion = 0;
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        delay(1000);

      }
      
    
    Serial.println("Nivel :" + String(nivel));
    Serial.println("Pulsacion :" + String(pulsacion));
    Serial.println("boton 1: " + String(pulsando));

    }
    else if(pulsacion_boton2 == HIGH && pulsacion_boton1 == HIGH){
      pulsando = 0;
    }

    if(pulsacion == nivel){
      nivel++;
      modo = 0;
      pulsacion = 0;
    }
    
  }

}
