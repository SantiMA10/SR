#include <SPI.h>
#include <Ethernet.h>
#include <DHT11.h> // Libreria externa
int pin_sensor = 8;

int pin_led = 4;

DHT11 dht11(pin_sensor);

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};
EthernetServer servidor(80); //Puerto en el 80
IPAddress dnServer(156, 35, 14 , 3);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);

// Que cada uno ponga la IP de su grupo 201, 202, 203
IPAddress ip(192, 168, 61, 203);

float temperatura = 11
, humedad = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  pinMode(pin_led, OUTPUT);
  servidor.begin();
  Serial.println("Setup");
  // Imprimir la IP
  Serial.println(Ethernet.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient cliente = servidor.available();

  if (cliente) {

    Serial.println("nueva peticion");
    String peticion = "";
    while (cliente.connected()) {
      if (cliente.available()) {

        char c = cliente.read(); //Leer  petición carácter a carácter
        peticion.concat(c); // concatenar en un string

        // Ha acabado la peticion http
        // Si contiene index responder con una web

        // la petición ha acabado '\n' y contiene la cadena "index"
        if (c == '\n' && peticion.indexOf("temperatura") != -1) {
          int codigo = readSensor();

          if(codigo == 0){
            cliente.println("HTTP/1.1 200");
            cliente.println("Content-Type: application/json");
            cliente.println();
            cliente.println("{\"temperatura : " + String(temperatura) + "}");
            break;
          }
          else{
            cliente.println("HTTP/1.1 400");
            cliente.println("Content-Type: application/json");
            cliente.println();
            cliente.println("{\"error\" : \"imposible leer el sensor\"}");
            break;
          }
          
        }

        if (c == '\n' && peticion.indexOf("todo") != -1) {
          int codigo = readSensor();

          if(codigo == 0){
            cliente.println("HTTP/1.1 200");
            cliente.println("Content-Type: application/json");
            cliente.println();
            cliente.println("{\"temperatura\" : " + String(temperatura) + ", \"humedad\" : " + String(humedad) + "}");
            break;
          }
          else{
            cliente.println("HTTP/1.1 400");
            cliente.println("Content-Type: application/json");
            cliente.println();
            cliente.println("{\"error\" : \"imposible leer el sensor\"}");
            break;
          }
          
        }

        if (c == '\n' && peticion.indexOf("humedad") != -1) {
          int codigo = readSensor();

          if(codigo == 0){
            cliente.println("HTTP/1.1 200");
            cliente.println("Content-Type: application/json");
            cliente.println();
            cliente.println("{\"humedad\" : " + String(humedad) + "}");
          }
          else{
            cliente.println("HTTP/1.1 400");
            cliente.println("Content-Type: application/json");
            cliente.println();
            cliente.println("{\"error\" : \"imposible leer el sensor\"}");
          }
          
          break;
          
        }

        if (c == '\n' && peticion.indexOf("encender") != -1) {
          digitalWrite(pin_led, HIGH);
          cliente.println("HTTP/1.1 200");
          cliente.println("Content-Type: application/json");
          cliente.println();
          
          break;
          
        }

        if (c == '\n' && peticion.indexOf("apagar") != -1) {
          digitalWrite(pin_led, LOW);
          cliente.println("HTTP/1.1 200");
          cliente.println("Content-Type: application/json");
          cliente.println();

          
          break;
          
        }
      }
    }

    // Pequeña pausa para asegurar el envio de datos
    delay(2000);
    cliente.stop();// Cierra la conexión
  }
      delay(100);

}

int readSensor() {
  int codigoSalida = dht11.read(humedad, temperatura);
  //int codigoSalida = 0;

  delay(7000); // Actualizar cada dos segundos

  return codigoSalida;
}

