#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESP8266WebServer.h>

extern ESP8266WebServer server;

void setupWebServer();
void handleRoot();
void handleON();
void handleOFF();
void handleSavePlantsNames();
void handleLoadPlantsNames();
void handleSensor1();
void handleSensor2();
void handleSensor3();
void handleSensor4();
void turnSensorsOff();

#endif