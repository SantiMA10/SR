int led1 = 2;
int led2 = 3;

int boton1 = 5;
int boton2 = 4;

int colores[10];
int nivel = 2;
int pulsacion = 0;
int pulsando = 0;

int modo = 0;

void generarNumeros() {
  int i;
  for(i = 0; i < sizeof(colores)/sizeof(int); i++){
    colores[i] = random(0,2);
    Serial.print(String(colores[i]));

    if(i < sizeof(colores)/sizeof(int)){
      Serial.print(",");
    }
  }
  Serial.println();
}

void mostrarCombinacion(){
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

void comprobarCombinacion(){

  digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    int pulsacion_boton1 = digitalRead(boton1);
    int pulsacion_boton2 = digitalRead(boton2);
    
    if(pulsacion_boton1 == LOW && pulsacion_boton2 == HIGH && pulsando == 0){
      pulsando = 1;
      if(colores[pulsacion] == 0){
        pulsacion++;
        delay(100);
      }
      else{
        reiniciarJuegoTrasFallo();
      }
    
      Serial.println("Nivel :" + String(nivel));
      Serial.println("Pulsacion :" + String(pulsacion));
      Serial.println("boton 0: " + String(pulsando));
    }
    else if(pulsacion_boton2 == LOW && pulsacion_boton1 == HIGH && pulsando == 0){
      
      pulsando = 1;
      if(colores[pulsacion] == 1){
        pulsacion++;
        delay(100);
      }
      else{
        reiniciarJuegoTrasFallo();
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

void reiniciarJuegoTrasFallo(){
  nivel = 2;
  modo = 0;
  pulsacion = 0;
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  delay(1000);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(500);
}

void setup() {
  Serial.begin(9600); // Iniciar el Serial
  Serial.println("Setup");

  randomSeed(analogRead(A0));  //Leemos el ruido de la salida analogica que nunca es la misma. De esta forma logramos que el valor de la semilla sea diferente siempre y asi logramos una 
                               // una secuencia aleatoria de numeros.
  generarNumeros();

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
}

void loop() {

  if(modo == 0){
    mostrarCombinacion();
  }
  else if(modo == 1){
    comprobarCombinacion();
  }

}
