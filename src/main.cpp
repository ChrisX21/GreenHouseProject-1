#include <Arduino.h>
#include "config.h"
#include "SoilSensor.h"
#include "LightSensor.h"
#include "DHTSensor.h"
#include "PumpMotor.h"

unsigned long lastReadTime = 0;
unsigned long lastWaterTime = 0;
bool hasWatered = false;

void setup() {
  Serial.begin(9600);
  initSoil();
  initLight();
  initDht();
  initMotor();
}

void loop() {
  // 1. Update the pump motor state (call on every loop pass)
  updateMotor();

  // 2. Everything else runs once per interval
  unsigned long now = millis();
  if (now - lastReadTime < READ_INTERVAL_MS) {  // less than 2 seconds since last read -> too early
    return;
  }
  lastReadTime = now;

  // 3. Read sensors
  int soil = readSoilPercent();
  int light = readLight();
  bool dht = readDht();
  float temp = getTemperature();
  int hum = getHumidity();

  // 4. Results
  Serial.print("Soil: ");
  Serial.print(soil); 
  Serial.print("%  ");

  Serial.print("Light: ");
  Serial.print(light);
  Serial.print("  ");

  if (dht) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print("°C  ");

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print("%");
  } else {
    Serial.print("======== [ERROR] DHT read failed ========");
  }
  Serial.println();

}