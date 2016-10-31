int motorPin1 = 4;  //1N4
int motorPin2 = 5;  //1N3
int motorPin3 = 6; //1N2
int motorPin4 = 7; //1N1

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin1, OUTPUT); 
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

}

void loop() {
  for (int i=0; i <= 512 ; i++){
      gira_antihorario(5); 
   } 
   delay(2000);
for (int i=0; i <= 512 ; i++){
      gira_horario(5); 
   } 
   delay(2000);//espera 2 segundos
} 

void gira_antihorario(int tiempoPausa)
{
  digitalWrite(motorPin1, HIGH); 
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(tiempoPausa);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(tiempoPausa);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);
  delay(tiempoPausa);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(tiempoPausa);  
}

void gira_horario(int tiempoPausa){
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(tiempoPausa); 
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);
  delay(tiempoPausa);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(tiempoPausa);
  digitalWrite(motorPin1, HIGH); 
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(tiempoPausa);
}

