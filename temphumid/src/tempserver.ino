#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_HDC1000.h>

#include "tempserver.h"

ESP8266WebServer server(80);

Adafruit_HDC1000 hdc = Adafruit_HDC1000();

const int led = 5;
String errMsg = "";
bool sensErr = false;

void handleRoot() {
  digitalWrite(led, 0);

  if (sensErr == true) {
     server.send(200, "text/plain", errMsg);
  } else {
    String temp = String(hdc.readTemperature());
    String hum = String(hdc.readHumidity());
    server.send(200, "text/plain", "temp:" + temp + ",humidity:" + hum);
  }


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

  Wire.begin(sdaPort, sclPort);

  if (!hdc.begin()) {
    sensErr = true;
    errMsg = "Couldn't find sensor!";
  }

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