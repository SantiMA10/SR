#include <SPI.h>  //Importamos librería comunicación SPI
#include <Ethernet.h>  //Importamos librería Ethernet
#include <DHT11.h> // Libreria externa
int pin_sensor = 8;
int pin_rele = 5;

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x29};
EthernetServer servidor(80); //Puerto en el 80
IPAddress dnServer(156, 35, 14, 2);
IPAddress gateway(156, 35, 98, 201);
IPAddress subnet(255, 255, 255, 0);

// Probar Ips a partir de las 200
IPAddress ip(156, 35, 98, 92);

float temperatura = -1,
      humedad = 0;

float temperatura_objetivo = 20.0;

float ultima = 0,
      tiempoEntreLecturas = 0;

DHT11 dht11(pin_sensor);

char server[] = "www.mderg.com";

void setup() {
  
  Serial.begin(9600);
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  servidor.begin();
  Serial.println("Setup");
  // Imprimir la IP
  Serial.println(Ethernet.localIP());

  // Inicializar el led
  pinMode(pin_rele, OUTPUT);
}

void loop() {
  EthernetClient cliente = servidor.available();
  comprobarTemperatura();
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

          if (codigo == 0) {
            cliente.println("HTTP/1.1 200");
            cliente.println("Content-Type: application/json");
            cliente.println();
            cliente.println("{\"temperatura\" : " + String(temperatura) + "}");
            break;
          }
          else {
            cliente.println("HTTP/1.1 400");
            cliente.println("Content-Type: application/json");
            cliente.println();
            cliente.println("{\"error\" : \"imposible leer el sensor\"}");
            break;
          }

        }
        else if (c == '\n' && peticion.indexOf("mas") != -1) {
          int codigo = readSensor();

          if (codigo == 0) {
            cliente.println("HTTP/1.1 200");
            cliente.println("Content-Type: application/json");
            cliente.println();
            temperatura_objetivo++;
            cliente.println("{\"temperatura actual\" : " + String(temperatura) + ", \"temperatura objetivo\" : " + String(temperatura_objetivo) + "}");
            break;
          }

        }
        else if (c == '\n' && peticion.indexOf("menos") != -1) {
          int codigo = readSensor();

          if (codigo == 0) {
            cliente.println("HTTP/1.1 200");
            cliente.println("Content-Type: application/json");
            cliente.println();
            temperatura_objetivo--;
            cliente.println("{\"temperatura actual\" : " + String(temperatura) + ", \"temperatura objetivo\" : " + String(temperatura_objetivo) + "}");
            break;
          }

        }
      }
    }

    // Pequeña pausa para asegurar el envio de datos
    delay(1000);
    cliente.stop();// Cierra la conexión
  }
}

int readSensor() {

  int codigoSalida = 0;
  if(millis() - ultima > tiempoEntreLecturas){
    codigoSalida = dht11.read(humedad, temperatura);
    //int codigoSalida = 0;
  
    delay(7000); // Actualizar cada dos segundos
    ultima = millis();
  }

  return codigoSalida;
}

void comprobarTemperatura(){

  readSensor();
  
  if(temperatura_objetivo <= temperatura){
    //Hacer peticion
    actualizar("6253798123", "Temperatura alcanzada: " + String(temperatura));
    digitalWrite(pin_rele, LOW);
  }
  else{
    digitalWrite(pin_rele, HIGH);
  }
  
}

void actualizar(String idNotificacion,String estado){
  EthernetClient cliente;

  if (cliente.connect(server, 80)) {
    Serial.println("conectado");
    
    cliente.println("GET robotica/notificaciones/agregar.php?i="
        +idNotificacion+"&t="+estado+" HTTP/1.1");
    cliente.println("Host: www.mderg.com");
    cliente.println("Connection: close");
    cliente.println();
    
    delay(3000); // Esperar por seguridad

    String respuesta;
    
    while (cliente.available()) {
        char c = cliente.read();
        respuesta+=c;
    } 
    if (!cliente.connected()) {
        Serial.println("respuesta -------------------------------");
        Serial.println(respuesta);
        Serial.println("Desconectado ---------------------------");
        cliente.stop();
    }
    
  } else {
    Serial.println("Fallo de conexión");
     // RESET a veces falla y hay que reiniciarlo
     cliente.stop();
     delay(1000);
     Ethernet.begin(mac, ip, dnServer, gateway, subnet);
     delay(1000);
   }
}


