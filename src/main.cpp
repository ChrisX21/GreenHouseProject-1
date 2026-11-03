#include <Arduino.h>
#include "config.h"
#include "SoilSensor.h"
#include "LightSensor.h"
#include "DHTSensor.h"
#include "PumpMotor.h"

enum PumpState { PUMP_IDLE, PUMP_WATERING };

PumpState pumpState = PUMP_IDLE;
unsigned long lastReadTime = 0;
unsigned long lastBurstEnd = 0;
unsigned long lastCycleEnd = 0;
bool hasWatered = false;
bool wasMoving = false;
uint8_t burstCount = 0;

void setup() {
  Serial.begin(9600);
  initSoil();
  initLight();
  initDht();
  initMotor();
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_WARN_LED, OUTPUT);
  digitalWrite(PIN_WARN_LED, LOW);
  digitalWrite(PIN_LED, LOW);
}

void endCycle(unsigned long now, const char* reason) {
  pumpState = PUMP_IDLE;
  lastCycleEnd = now;
  hasWatered = true;
  Serial.print("[PUMP] cycle done (");
  Serial.print(reason);
  Serial.println(")");
}

// Watering system (flowchart): M <= DRY -> pump ON, keep going until M >= WET -> OFF.
// The pump runs in bursts with a soak pause in between, because water takes
// a while to reach the sensor.
void updateWateringSystem(int soil, unsigned long now) {
  switch (pumpState) {
    case PUMP_IDLE: {
      bool cooledDown = !hasWatered || (now - lastCycleEnd >= WATER_COOLDOWN_MS);
      if (soil <= SOIL_DRY_PERCENT && cooledDown) {
        pumpState = PUMP_WATERING;
        burstCount = 1;
        startWatering(WATER_STEPS);
        Serial.println("[PUMP] ON");
      }
      break;
    }

    case PUMP_WATERING: {
      if (soil >= SOIL_WET_PERCENT) {
        endCycle(now, "target reached");
      } else if (now - lastBurstEnd >= WATER_SOAK_MS) {
        if (burstCount >= WATER_MAX_BURSTS) {
          endCycle(now, "max bursts, check tank/sensor");
        } else {
          burstCount++;
          startWatering(WATER_STEPS);
        }
      }
      break;
    }
  }
}

// Light system: readLight() is higher = darker, so dark -> LED ON.
// The LDR is positioned so the LED doesn't change its reading (no feedback loop),
// but a small deadband still stops flicker when the reading hovers at the threshold.
bool ledOn = false;

void updateLightSystem(int light) {
  if (!ledOn && light > LIGHT_DARK_THRESHOLD) {
    ledOn = true;
  } else if (ledOn && light < LIGHT_DARK_THRESHOLD - LIGHT_HYSTERESIS) {
    ledOn = false;
  }
  digitalWrite(PIN_LED, ledOn ? HIGH : LOW);
}

void loop() {
  // 1. Update the pump motor state (call on every loop pass)
  updateMotor();

  // Remember when a burst finishes (used for the soak pause)
  bool moving = isWatering();
  if (wasMoving && !moving) {
    lastBurstEnd = millis();
  }
  wasMoving = moving;

  // 2. While the motor is moving, do nothing else: sensor reads and serial
  //    prints block for 100+ ms and would make the stepper stutter.
  if (moving) {
    return;
  }

  // 3. Everything else runs once per interval
  unsigned long now = millis();
  if (now - lastReadTime < READ_INTERVAL_MS) {
    return;
  }
  lastReadTime = now;

  // 4. Read sensors
  int soil = readSoilPercent();
  int light = readLight();
  bool dht = readDht();
  float temp = getTemperature();
  int hum = getHumidity();

  // 5. Control logic
  updateWateringSystem(soil, now);
  updateLightSystem(light);

  // 6. Serial output
  Serial.print("Soil: ");
  Serial.print(soil);
  Serial.print("%  ");

  Serial.print("Light: ");
  Serial.print(light);
  Serial.print("  ");

  Serial.print("Pump: ");
  Serial.print(pumpState == PUMP_WATERING ? "WATERING" : "IDLE");
  Serial.print("  ");

  bool hot = false;
if (dht) {
  hot = temp > TEMP_HIGH_C;
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

if (hot) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(PIN_WARN_LED, HIGH);
    delay(50);
    digitalWrite(PIN_WARN_LED, LOW);
    delay(50);
  }
}
}