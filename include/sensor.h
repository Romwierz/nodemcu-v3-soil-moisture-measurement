#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

void setUpSensors();
uint16_t moistureRead1();
uint16_t moistureRead2();
uint16_t moistureRead3();
uint16_t moistureRead4();
void updateLastRequestTime();
void isClientInactive();

#endif