#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "tempserver.h"

ESP8266WebServer server(80);

const int led = 5;

void handleRoot() {
  digitalWrite(led, 0);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 1);
}

void handleNotFound(){
  digitalWrite(led, 0);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 1);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  WiFi.hostname(wifiHostname);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led, 1);
    delay(100);
    digitalWrite(led, 0);
    delay(400);
  }
  digitalWrite(led, 1);

  server.onNotFound(handleNotFound);

  server.on("/", handleRoot);

  server.begin();
}

void loop(void){
  server.handleClient();
}