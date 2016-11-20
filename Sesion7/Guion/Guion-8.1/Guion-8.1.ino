#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};  
EthernetServer servidor(80); //Puerto en el 80
IPAddress dnServer(156, 35, 14 , 3);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);

// Que cada uno ponga la IP de su grupo 201, 202, 203 
IPAddress ip(192, 168, 61, 203);

int led = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  servidor.begin();
   Serial.println("Setup");
  // Imprimir la IP
  Serial.println(Ethernet.localIP());
  
   // Inicializar el led
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
    EthernetClient cliente = servidor.available(); 

  if (cliente) {


Serial.println("nueva peticion");
    String peticion=""; 
    while (cliente.connected()) {
      if (cliente.available()) {
        
        char c = cliente.read(); //Leer  petición carácter a carácter
        peticion.concat(c); // concatenar en un string
 
        // Ha acabado la peticion http
        // Si contiene index responder con una web
      
        // la petición ha acabado '\n' y contiene la cadena "index"
        if (c == '\n' && peticion.indexOf("index") != -1) {
            Serial.println("Responder");
            // Serial.println(peticion);
            
            // contiene la cadena "encender+"
            if(peticion.indexOf("encender") != -1 )
            {
              digitalWrite(led,HIGH);
              Serial.println("Encender Led");
            }
            // contiene la cadena "apagar"
            if(peticion.indexOf("apagar") != -1)
            {
              Serial.println("Apagar led");
              digitalWrite(led,LOW);
            }
            
            // Enviamos al cliente una respuesta HTTP
            cliente.println("HTTP/1.1 200 OK");
            cliente.println("Content-Type: text/html");
            cliente.println();
            break;
        }
      }
    }
    
    // Pequeña pausa para asegurar el envio de datos
    delay(1000);
    cliente.stop();// Cierra la conexión
  }
}

