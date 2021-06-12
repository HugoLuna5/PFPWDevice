#include "DHTesp.h" // Incluyo la librería DHTesp
DHTesp dht;

const char* ssid = "Luna Inc";
const char* password = "Ydfmx69VN!74";
const char* host = "192.168.1.74";

const char* statusOK = "OK";

float parametro1;
float parametro2;

/************************************************************************************************
 ************************************************************************************************/

void setup() {
  Serial.begin(115200); 
  delay(1);
  dht.setup(22,DHTesp::DHT11);
  //Serial.print("conectando a ");
  //Serial.println(ssid);
  //WiFi.begin(ssid, password);

  /*
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("direccion IP: ");
  Serial.println(WiFi.localIP());
   * 
   */
}

/***********************************************************
 ***********************************************************/
 
void loop() {

  /*
   Serial.print("conectado a ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Fallo conexion");
    return;
  }
   */


      delay(dht.getMinimumSamplingPeriod());
      float humidity = dht.getHumidity(); // obtenemos la humedad
      float temperature = dht.getTemperature(); //obtenemos la temperatura

      if(dht.getStatusString() == statusOK){
        Serial.print("Temperatura: ");
        Serial.print(temperature);
        Serial.print(" Humedad: ");
        Serial.print(humidity);
        Serial.println();
      }

     

/*
         
  // We now create a URI for the request
  String url = "/save_as.php?";
  url += "temperatura=";
  url += parametro1;
  
 url += "&humedad=";
 url += parametro2;

  Serial.print("Buscando URL: ");
  Serial.println(url);

  //..................................//
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("conexiÛn de cierre");
  delay(10000);
 */
  
}
