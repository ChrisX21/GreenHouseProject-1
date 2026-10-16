#include <Arduino.h>
#include "LightSensor.h"
#include "config.h"

void initLight() {
  pinMode(PIN_LDR, INPUT);
}

int readLight() {
  return 1023 - analogRead(PIN_LDR);   // higher = darker
}

bool isDark() {
  return readLight() > LIGHT_DARK_THRESHOLD;
}