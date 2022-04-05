#include <ESP8266WiFi.h>
const char* ssid     = "Flia Claros"; // Your ssid
const char* password = "diegopolo"; // Your Password
float temp_celsius = 0;
WiFiServer server(80);
void setup() {
 Serial.begin(115200);
  pinMode(A0, INPUT);   
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi is connected");
server.begin();
Serial.println("Server started");
Serial.println(WiFi.localIP());
}
void loop() {
temp_celsius = (analogRead(A0) * 330.0) / 1023.0;
Serial.print("  Temperatura = ");
Serial.print(temp_celsius);
Serial.println(" Celsius, ");

WiFiClient client = server.available();
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");  // the connection will be closed after completion of the response
client.println("Refresh: 3");  // update the page after 10 sec
client.println();
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.print("<p style='text-align: center;'><span style='font-size: x-large;font-family: Helvetica;'><strong>SENSOR DE TEMPERATURA</strong></span></p>");
client.print("<p style='text-align: center;'><span style='color: #000000;'><strong style='font-size: large;font-family: Helvetica;'>Temperatura (*C)= ");
client.println(temp_celsius);
client.print("</p>");
client.println("</html>");
delay(5000);
}
