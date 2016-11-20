#include <DHT11.h> // Libreria externa
int pin_sensor = 8;

DHT11 dht11(pin_sensor);

void setup(){
   Serial.begin(9600);
}

void loop(){
    float temperatura, humedad;
    int codigoSalida = dht11.read(humedad, temperatura);
     
    if( codigoSalida == 0) { // Tiene que retornar 0, 
           Serial.println("Temperatura: "+String(temperatura));
           Serial.println("Humedad: "+String(humedad));
           Serial.println("--------------------------------");
    } else {
        // No retorna 0 hay un error
        Serial.println("Error:"+String(codigoSalida));
     }
       
    delay(2000); // Actualizar cada dos segundos
}

