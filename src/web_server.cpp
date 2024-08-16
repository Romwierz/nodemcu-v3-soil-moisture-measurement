#include <FS.h>
#include "web_server.h"
#include "sensor.h"
#include "pins.h" 

ESP8266WebServer server(80);

void setupWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleON);
  server.on("/off", HTTP_GET, handleOFF);
  server.on("/save", HTTP_POST, handleSavePlantsNames);
  server.on("/load", HTTP_GET, handleLoadPlantsNames);
  server.on("/sensor1", HTTP_GET, handleSensor1);
  server.on("/sensor2", HTTP_GET, handleSensor2);
  server.on("/sensor3", HTTP_GET, handleSensor3);
  server.on("/sensor4", HTTP_GET, handleSensor4);
  server.on("/turnSensorsOff", HTTP_GET, turnSensorsOff);

  server.begin();
}

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (file) {
    server.streamFile(file, "text/html");
    file.close();
  }
}

void handleON() {
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/plain", "LED on");
}

void handleOFF() {
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/plain", "LED off");
}

void handleSavePlantsNames() {
  if (server.hasArg("plain")) {
    String json = server.arg("plain");
    File file = SPIFFS.open("/plants_names.txt", "w");
    if (!file) {
      server.send(500, "text/plain", "Failed to save values");
      return;
    }
    file.print(json);
    file.close();
    server.send(200, "text/plain", "Values saved successfully");
  } else {
    server.send(400, "text/plain", "Bad Request: No data received");
  }
}

void handleLoadPlantsNames() {
  File file = SPIFFS.open("/plants_names.txt", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to load values");
    return;
  }
  String json = file.readString();
  file.close();
  server.send(200, "application/json", json);
}

void handleSensor1() {
  updateLastRequestTime();
  uint16_t moisture = moistureRead1();
  server.send(200, "text/plain", String(moisture));
}

void handleSensor2() {
  updateLastRequestTime();
  uint16_t moisture = moistureRead2();
  server.send(200, "text/plain", String(moisture));
}

void handleSensor3() {
  updateLastRequestTime();
  uint16_t moisture = moistureRead3();
  server.send(200, "text/plain", String(moisture));
}

void handleSensor4() {
  updateLastRequestTime();
  uint16_t moisture = moistureRead4();
  server.send(200, "text/plain", String(moisture));
}

void turnSensorsOff() {
  digitalWrite(SENSOR1_PIN, LOW);
  digitalWrite(SENSOR2_PIN, LOW);
  digitalWrite(SENSOR3_PIN, LOW);
  digitalWrite(SENSOR4_PIN, LOW);
  server.send(200, "text/plain", "All sensors turned off");
}