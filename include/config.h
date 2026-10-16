#ifndef CONFIG_H
#define CONFIG_H

// ---------- Arduino Uno Pins ----------
#define PIN_LDR       A0
#define PIN_SOIL      A1
#define PIN_DHT       2

// Stepper driver inputs, in AccelStepper order for 28BYJ-48: IN1, IN3, IN2, IN4
#define PIN_STEP_1    8
#define PIN_STEP_2    10
#define PIN_STEP_3    9
#define PIN_STEP_4    11

// ---------- Soil calibration ----------
#define SOIL_DRY_VALUE   740   // raw value in open air
#define SOIL_WET_VALUE   454   // raw value in water

// ---------- Thresholds ----------
#define SOIL_DRY_PERCENT       30    // below this -> water the plant
#define LIGHT_DARK_THRESHOLD   800   // above this = dark
#define TEMP_HIGH_C            30    // above this = warn
#define HUMIDITY_HIGH_PERCENT  80    // above this = warn

// ---------- Timing ----------
#define READ_INTERVAL_MS     2000UL    // unsigned long: how often main.cpp reads sensors, DHT11 needs at least 2 s between reads
#define WATER_COOLDOWN_MS    60000UL   // unsigned long: 60s minimum wait between two watering actions

// ---------- Motor ----------
#define MOTOR_MAX_SPEED      1000
#define MOTOR_ACCELERATION   500
#define WATER_STEPS          4096      // one full turn in half-step mode

#endif