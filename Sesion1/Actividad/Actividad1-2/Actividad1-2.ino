int led1 = 2;
int led2 = 3;

int boton1 = 4;
int boton2 = 5;

int colores[10]:
int nivel = 2;

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
    colores[i] = random(0,1);
    Serial.print(", " + String(colores[i]));
  }
  Serial.println();

}

void loop() {

  if(modo == 0){
    
    for(i = 0; i < nivel; i++){
      if(colores[i] == 0){
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
      }
      else if(colores[i] == 1){
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
      }
    }
    modo = 1;
  }
  else if(modo == 1){

    int pulsacion = 0;

    

    colores[pulsacion] 
    
  }

}
