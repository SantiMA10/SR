#include <TM1637.h>

long distancia;

int pinClk = 3;
int pinDio = 4;

TM1637 pantalla(pinClk,pinDio);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pantalla.init();
  pantalla.set(BRIGHT_TYPICAL); 
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
 
  delay(1500);//Delay to let system boot


}

void loop() {
  // put your main code here, to run repeatedly:
  distancia = 7373;
  
  int digito0 = distancia/1000;    
  Serial.println("digito0 "+ String(digito0)); 

  int digito1 = (distancia - digito0*1000)/100; 
  Serial.println("digito1 "+ String(digito1));

  int digito2 = (distancia - (digito0*1000 + digito1*100))/10;  
  Serial.println("digito2 "+ String(digito2));

  int digito3 = distancia - (digito0*1000 + digito1*100 + digito2*10);
  Serial.println("digito3 "+ String(digito3));
  
  pantalla.display(0,digito0);
  pantalla.display(1,digito1);
  pantalla.display(2,digito2);
  pantalla.display(3,digito3);

}
