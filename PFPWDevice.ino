

#if defined(ARDUINO_ESP8266_NODEMCU)
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  int pin = D2;
#else
  #include <HTTPClient.h>
  int pin = 22;
#endif


#include "DHTesp.h" // Incluyo la librería DHTesp
DHTesp dht;

unsigned long lastMotorRunTime;


const char* ssid = "Luna Inc";
const char* password = "Ydfmx69VN!74";
String urlRequest = "http://192.168.1.79:8080/api/v1/device/save";
String device_uuid = "PFPW60c485af4b5c8";
String token = "Bearer BB28zTNUInRYqRjtrTN8gjEtkkvz8eiBJsfs24bb";

const char* statusOK = "OK";


HTTPClient httpClientTemp;

/************************************************************************************************
 ************************************************************************************************/

void setup() {
  Serial.begin(115200); 
  delay(1);
  dht.setup(pin,DHTesp::DHT11);
  Serial.print("conectando a ");
  Serial.println(ssid);
  
   WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("direccion IP: ");
  Serial.println(WiFi.localIP());
   

 
}

/***********************************************************
 ***********************************************************/
 
void loop() {


      Serial.println("GG");
      delay(dht.getMinimumSamplingPeriod());
      float humidity = dht.getHumidity(); // obtenemos la humedad
      float temperature = dht.getTemperature(); //obtenemos la temperatura

      

      if(dht.getStatusString() == statusOK){
//3,600,000
        if(millis()-lastMotorRunTime > 900000)  // 15 minutes have passed
    {
          Serial.print("Temperatura: ");
        Serial.print(temperature);
        Serial.print(" Humedad: ");
        Serial.print(humidity);
        Serial.println();

        //clientTemp.setInsecure(); //the magic line, use with caution
        //clientTemp.connect(urlRequest, 8080);
        httpClientTemp.begin(urlRequest);
        httpClientTemp.addHeader("Content-Type", "application/json");
        httpClientTemp.addHeader("Authorization", token);
        String idSensorDevice = "1";
        String body = "{\"token\":\""+device_uuid+"\",\"values\":[{\"item\":\"Humedad\",\"valor\":\""+humidity+"\"},{\"item\":\"Temperatura\",\"valor\":\""+temperature+"\"}],\"sensor_device_id\": \""+idSensorDevice+"\"}";
        int httpResponseCode = httpClientTemp.POST(body);
        if  (httpResponseCode > 0){
            
            Serial.print("ResponseCode: ");
            Serial.println(httpResponseCode);
           }
          httpClientTemp.end();        
         lastMotorRunTime = millis();
    }
    delay(100); // loop about every 1/10 second, or whatever works
        
       
       
       }

      

     


  
}
