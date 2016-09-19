int valorPotenciometro;
int led1 = 2;
int led2 = 3;
int led3 = 4;

void setup() {
  Serial.begin(9600); // Iniciar el Serial
  Serial.println("Setup");

 // Los pins digitales se declaran - LED
  pinMode(led1, OUTPUT); // Salida
  pinMode(led2, OUTPUT); // Salida
  pinMode(led3, OUTPUT); // Salida

}

void loop() {
  // put your main code here, to run repeatedly:
   // Leemos el valor del pin A0 - Potenciometro
   valorPotenciometro = analogRead(A0); // 0 - 1024
   Serial.println("valor: "+String(valorPotenciometro));
  
   if(valorPotenciometro >= 0 && valorPotenciometro < 1023/3){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
   }
   else if((valorPotenciometro >= (1023/3) && valorPotenciometro < (1023/3)*2)){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
   }
   else if(valorPotenciometro >= (1023/3)*2 && valorPotenciometro < 1023){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
   }

}
