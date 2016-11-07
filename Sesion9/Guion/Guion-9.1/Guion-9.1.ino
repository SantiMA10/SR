#include <SPI.h>
#include <Ethernet.h>

// IMPORTANTE!!!!!CADA UNO QUE PONGA UNA MAC 
// ultimo digito segun su grupo 0x21 - 0x22 , 0x22
byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};  
IPAddress dnServer(156, 35, 14 , 2);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);
// IMPORTANTE!!!!!CADA UNO QUE PONGA UNA IP
// ultimo digito según su grupo 51, 52, 53, 54
IPAddress ip(192, 168, 61, 250);

char server[] = "www.mderg.com";
EthernetClient client;

int pin_sensor = 7;
int ultimoValor = -1;
long ultimoValorTime = 0;
String identificadorPlaza = "666";

void setup() {
  Serial.begin(9600);
  pinMode(pin_sensor, INPUT);
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  Serial.println(Ethernet.localIP());
  delay(1000);
}


void loop() {
  int valorActual = digitalRead(pin_sensor);
  
  if (millis() - ultimoValorTime > 3000 && valorActual != ultimoValor){
     Serial.println("Enviar peticion valor="+String(valorActual));
actualizar(identificadorPlaza, String(valorActual));
     
     ultimoValor = valorActual; // Actualizar ultimo valor
     ultimoValorTime = millis();
  }
}

String respuesta = "";
void actualizar(String idPlaza,String estadoPlaza){
  if (client.connect(server, 80)) {
    Serial.println("conectado");
    
    client.println("GET /robotica/parking13/actualizarplazag.php?i="
+idPlaza+"&o="+estadoPlaza+" HTTP/1.1");
    client.println("Host: www.mderg.com");
    client.println("Connection: close");
    client.println();
    
    delay(3000); // Esperar por seguridad
    
    while (client.available()) {
        char c = client.read();
        respuesta+=c;
    } 
    if (!client.connected()) {
        Serial.println("respuesta -------------------------------");
        Serial.println(respuesta);
        Serial.println("Desconectado ---------------------------");
        client.stop();
    }
    
  } else {
    Serial.println("Fallo de conexión");
     // RESET a veces falla y hay que reiniciarlo
     client.stop();
     delay(1000);
     Ethernet. begin(mac, ip, dnServer, gateway, subnet);
     delay(1000);
   }
}

