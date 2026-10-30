#ifndef CONFIG_H
#define CONFIG_H

// ---------- Arduino Uno Pins ----------
#define PIN_LDR       A0
#define PIN_SOIL      A1
#define PIN_DHT       2
#define PIN_LED       3      // LED (pin 3 is also PWM-capable if you ever want dimming)
#define PIN_WARN_LED  4

// Stepper driver inputs, in AccelStepper order for 28BYJ-48: IN1, IN3, IN2, IN4
#define PIN_STEP_1    8
#define PIN_STEP_2    10
#define PIN_STEP_3    9
#define PIN_STEP_4    11

// ---------- Soil calibration ----------
#define SOIL_DRY_VALUE   740   // raw value in open air
#define SOIL_WET_VALUE   454   // raw value in water

// ---------- Thresholds ----------
#define SOIL_DRY_PERCENT       30    // at or below this -> start watering
#define SOIL_WET_PERCENT       60    // NEW: at or above this -> stop watering
#define LIGHT_DARK_THRESHOLD   600   // above this = dark -> LED on
#define LIGHT_HYSTERESIS       30    // NEW: LED turns off again below (threshold - this), stops flicker from sensor noise
#define TEMP_HIGH_C            24    // above this = warn
#define HUMIDITY_HIGH_PERCENT  80    // above this = warn

// ---------- Timing ----------
#define READ_INTERVAL_MS     2000UL    // how often main.cpp reads sensors, DHT11 needs at least 2 s between reads
#define WATER_COOLDOWN_MS    30000UL   // minimum wait between two watering cycles
#define WATER_SOAK_MS        15000UL   // NEW: wait after each burst so water reaches the sensor
#define WATER_MAX_BURSTS     6         // NEW: safety limit per cycle (empty tank / dead sensor)

// ---------- Motor ----------
#define MOTOR_MAX_SPEED      1000
#define MOTOR_ACCELERATION   500
#define WATER_STEPS          4096      // one burst = one full turn in half-step mode

#endif