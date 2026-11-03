#include <Arduino.h>
#include "SoilSensor.h"
#include "config.h"

void initSoil() {
  pinMode(PIN_SOIL, INPUT);
}

int readSoilAveraged() {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(PIN_SOIL);
    delay(10);
  }
  return sum / 10;
}

int readSoilPercent() {
  int raw = readSoilAveraged();
  int percent = map(raw, SOIL_DRY_VALUE, SOIL_WET_VALUE, 0, 100);
  return constrain(percent, 0, 100);
}