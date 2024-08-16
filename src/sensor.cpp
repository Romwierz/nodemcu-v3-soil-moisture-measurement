#include "sensor.h"
#include "pins.h" 

#define ADC_MVOLT_MAX          3300UL
#define ADC_RAW_MAX            0x03FFUL
#define DIODE_MVOLT            320UL
#define ADC_DIODE_VOLTAGE_RAW  (DIODE_MVOLT * ADC_RAW_MAX) / ADC_MVOLT_MAX

#define ADC_TO_MOISTURE(adc) (100 - (((adc + ADC_DIODE_VOLTAGE_RAW) * 100) / ADC_RAW_MAX))

unsigned long lastRequestTime = 0;
const unsigned long timeoutInterval = 5000; // 5 seconds

void setUpSensors() {
  pinMode(SENSOR1_PIN, OUTPUT);
  pinMode(SENSOR2_PIN, OUTPUT);
  pinMode(SENSOR3_PIN, OUTPUT);
  pinMode(SENSOR4_PIN, OUTPUT);
}

void updateLastRequestTime() {
  lastRequestTime = millis();
}

uint16_t moistureRead1() {
  digitalWrite(SENSOR2_PIN, LOW);
  digitalWrite(SENSOR3_PIN, LOW);
  digitalWrite(SENSOR4_PIN, LOW);
  digitalWrite(SENSOR1_PIN, HIGH);
  return ADC_TO_MOISTURE(analogRead(A0));
}

uint16_t moistureRead2() {
  digitalWrite(SENSOR1_PIN, LOW);
  digitalWrite(SENSOR3_PIN, LOW);
  digitalWrite(SENSOR4_PIN, LOW);
  digitalWrite(SENSOR2_PIN, HIGH);
  return ADC_TO_MOISTURE(analogRead(A0));
}

uint16_t moistureRead3() {
  digitalWrite(SENSOR1_PIN, LOW);
  digitalWrite(SENSOR2_PIN, LOW);
  digitalWrite(SENSOR4_PIN, LOW);
  digitalWrite(SENSOR3_PIN, HIGH);
  return ADC_TO_MOISTURE(analogRead(A0));
}

uint16_t moistureRead4() {
  digitalWrite(SENSOR1_PIN, LOW);
  digitalWrite(SENSOR2_PIN, LOW);
  digitalWrite(SENSOR3_PIN, LOW);
  digitalWrite(SENSOR4_PIN, HIGH);
  return ADC_TO_MOISTURE(analogRead(A0));
}

void isClientInactive() {
  if (millis() - lastRequestTime >= timeoutInterval) {
    digitalWrite(SENSOR1_PIN, LOW);
    digitalWrite(SENSOR2_PIN, LOW);
    digitalWrite(SENSOR3_PIN, LOW);
    digitalWrite(SENSOR4_PIN, LOW);
    lastRequestTime = millis(); // Reset to current time
  }
}