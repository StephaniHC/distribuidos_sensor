#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#define DHTTYPE DHT11
#define DHTPIN D1
int port = 6000;
const uint32_t chipId = ESP.getChipId();
const char* host = "192.168.0.20";
const char* ssid = "Flia.Guzman";
const char* password = "fliaguzman7890";
// GMT-4 - Bolivia | For UTC-4.00 : -4 * 60 * 60 : -14400
const long utcOffsetInSeconds = -4 * 60 * 60;
String auxiliar;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);
  dht.begin();   
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  // Wait for connection  
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {   
    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  Serial.print("Puerto: ");
  Serial.println(port);

}

void loop() {
   WiFiClient client;
  if (!client.connect(host,port)){
    Serial.println("Conexion Fallida.");
    delay(5000);
    return;
  } 
  //String idCliente=client.readStringUntil('\n');
  //Serial.println("Id Asignado: " + idCliente);
  while(client.connected()){
    time_t epochTime = timeClient.getEpochTime();
    double tem = dht.readTemperature();
    double hum = dht.readHumidity();
    Serial.println( "Id=" + String(chipId) + "|Temp=" + String(tem) + "|Hum=" + String(hum) + "|Tiempo=" + String(epochTime));
    Serial.println("Enviando a:"+String(host));
    client.print( "Id=" + String(chipId)+ "|Temp=" + String(tem) + "|Hum=" + String(hum) + "|Tiempo=" + String(epochTime));
    delay(30000);
  }
  
  Serial.println("");
  Serial.println("Dispositivo desconectado");
  client.stop(); 
}
