#include <Arduino.h>
#include <Bonezegei_DHT11.h>
#include "DHTSensor.h"
#include "config.h"

static Bonezegei_DHT11 dht(PIN_DHT);
static float lastTemperature = 0;
static int lastHumidity = 0;

void initDht() {
  dht.begin();
}

bool readDht() {
  if (dht.getData()) {
    lastTemperature = dht.getTemperature();
    lastHumidity = dht.getHumidity();
    return true;
  }
  return false;
}

float getTemperature() {
  return lastTemperature;
}

int getHumidity() {
  return lastHumidity;
}