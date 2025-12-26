#include <WiFi.h>
const char* SSID = "esp32";
const char* PASS = "mypassword"; //minimum of 8
void setup(){
  Serial.begin(115200);
  WiFi.softAP(SSID, PASS);
  Serial.println("Wifi access point started!");
}
void loop() {}
