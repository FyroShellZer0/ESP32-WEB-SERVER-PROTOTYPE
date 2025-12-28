#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DNSServer.h>

const char* SSID = "MyESP32";
const char* Password = "12345678";
const char* hostname = "mydevice";

WebServer server(80);
DNSServer dnsServer; //DNS OBJECT CREATION
const byte DNS_PORT = 53; //PORT 53

void setup() {
  Serial.begin(115200);
  
  WiFi.softAP(SSID, Password);
  WiFi.setHostname(hostname);

  IPAddress ip = WiFi.softAPIP(); //assign ip address to "ip"

  // Start DNS (catch ALL domains)
  dnsServer.start(DNS_PORT, "*", ip); //Listen on port 53 (DNS port) && "*" = match ALL domain names
  // connectivitycheck.gstatic.com → 192.168.4.1
  // msftconnecttest.com          → 192.168.4.1
  // randomsite.com               → 192.168.4.1 ALL LEADS TO THE SERVER
  
  
  // Start mDNS service
  MDNS.begin(hostname);
  MDNS.addService("http", "tcp", 80);
  
  server.on("/", []() {
    server.send(200, "text/html", 
    "<h1>ESP32</h1>"
    "<p>You are now connected!</p>"
    );
  });
  server.onNotFound([](){
    server.sendHeader("location", "http://192.168.4.1/");
    server.send(302, "text/html", //302 Found 
    "<h1>ESP32 Captive Portal</h1>"
    "<p>Redirected automatically</p>");
  });
  server.begin();
  
  Serial.print("IP: ");
  Serial.println(ip);
  Serial.print("Hostname: ");
  Serial.print(hostname);
  Serial.println(".local");
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}
