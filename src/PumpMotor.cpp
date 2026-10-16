#include <Arduino.h>
#include <AccelStepper.h>
#include "PumpMotor.h"
#include "config.h"

static AccelStepper stepper(AccelStepper::HALF4WIRE,
                            PIN_STEP_1, PIN_STEP_2, PIN_STEP_3, PIN_STEP_4);

void initMotor() {
  stepper.setMaxSpeed(MOTOR_MAX_SPEED);
  stepper.setAcceleration(MOTOR_ACCELERATION);
}

void startWatering() {
  if (!isWatering()) {
    stepper.move(WATER_STEPS);
  }
}

void updateMotor() {
  stepper.run();
}

bool isWatering() {
  return stepper.distanceToGo() != 0;
}