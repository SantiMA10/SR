int pin = 8;

void setup() {
  Serial.begin(9600);       
  pinMode(pin, INPUT);   
}

void loop() {
  Serial.println("Sensor Crash: "+String(digitalRead(pin)));
}

