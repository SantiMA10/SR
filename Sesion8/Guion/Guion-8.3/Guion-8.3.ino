float RO;
int pin_sensor = A0;

void setup() {
  Serial.begin(9600);
  // Calibrar en base al ambiente
  calibrarRO();
}
 
void loop() {
 
  float voltaje;
  float gas; // Get value of RS in a GAS
  float ratio; // Get ratio RS_GAS/RS_air
  int valorSensor = analogRead(pin_sensor);
  
  voltaje = (float)valorSensor/1024*5.0;
  gas = (5.0-voltaje)/voltaje; // omit *RL
  ratio = gas/RO;  // ratio = RS/R0 
 
  Serial.println("Voltaje = "+String(voltaje));
  Serial.println("Gas = "+String(gas));
  Serial.println("Ratio de Gas en Aire = "+String(ratio));
  delay(1000);
}


void calibrarRO(){
  float voltaje; 
  float aireLimpio; //  Get the value of RS via in a clear air
  float valorSensor;
 
  // Hacer la media de 100 mediciones
  for(int x = 0 ; x < 100 ; x++)
  {
    valorSensor = valorSensor + analogRead(pin_sensor);
  }
  valorSensor = valorSensor / 100.0;

  // El valorSensor medio con el aire limpio
  voltaje = (valorSensor/1024) * 5.0;
  aireLimpio = (5.0-voltaje) / voltaje; 
  RO = aireLimpio/9.8; // 9.8 es aire limpio
 
  Serial.println("R0 = "+String(RO));
}

