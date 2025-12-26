
#include <WiFi.h>
#include <WebServer.h>

// Customize these values
const char* customSSID = "MyESP32_Network";
const char* customPassword = "esp32password";  // Minimum 8 characters
WebServer server(80); //http port 80 || Creates a web server object named server
void setup() {
  Serial.begin(115200);
  
  // Create AP with custom SSID and password
  WiFi.softAP(customSSID, customPassword);

  //web sever 
  server.on("/", []() { //server.on("/", ...) = "When someone visits the homepage && "/" = Root URL (like "google.com/") && []() { ... } = Lambda function (anonymous function)
    server.send(200, "text/html", //sends a webpage && 200 = HTTP "OK" status code && "text/html" = Content type (it's HTML)
    "<h1>Title</h1>"
    "<p> sample web prototype</p>");
  });
  server.begin(); //start server
  Serial.println("Wi-Fi Access Point Started!");
}

void loop() {
  server.handleClient(); //Checks for incoming web requests || handle the client who will access the web server
}
