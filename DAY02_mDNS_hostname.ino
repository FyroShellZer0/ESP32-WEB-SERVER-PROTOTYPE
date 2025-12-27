#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
const char* SSID = "esp32";
const char* PASS = "12345678";
const char* hostname = "mydevice";
WebServer server(80); //creates a http server
void setup() {
  Serial.begin(115200); //start serial commu && 115200 baud rate = fast
  WiFi.softAP(SSID, PASS); //WIFI ACCESS POINT
  WiFi.setHostname(hostname);//sets the wifi hostname to the network 
  MDNS.begin(hostname); //allows access
  MDNS.addService("http", "tcp", 80); //type: http, protocol: tcp, port: 80
  server.on("/", []() {
    server.send(200, "text/html", "<h1> HELLO</h1>"); //200 = OK, CONTENT TYPE: TEXT/HTML RESPONSE BODY: <h1>HELLO</h1>
  });
  server.begin(); //START LISTENING FOR HTTP REQUEST
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP()); //IP: 192.168.4.1
  Serial.print("Hostname: ");
  Serial.print(hostname);
  Serial.println(".local");// mydevice.local
}
void loop() {
  server.handleClient(); //runs continuous and checks for new http request, client connection
}
