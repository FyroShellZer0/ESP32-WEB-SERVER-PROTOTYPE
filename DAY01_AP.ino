#include <WiFi.h>
void setup() {
  Serial.begin(115200);
  Wifi.softAP("ESP WIFI");
  Serial.println(WiFi.softAP);
}
void loop() {}
