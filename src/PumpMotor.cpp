#include <Arduino.h>
#include <AccelStepper.h>
#include "PumpMotor.h"
#include "config.h"

static AccelStepper stepper(AccelStepper::HALF4WIRE,
                            PIN_STEP_1, PIN_STEP_2, PIN_STEP_3, PIN_STEP_4);
static bool wasRunning = false;

void initMotor() {
  stepper.setMaxSpeed(MOTOR_MAX_SPEED);
  stepper.setAcceleration(MOTOR_ACCELERATION);
  stepper.disableOutputs();            // don't heat the coils while idle
}

void startWatering(long steps) {
  if (isWatering()) return;            // never stack moves
  stepper.enableOutputs();
  stepper.move(steps);
}

void updateMotor() {
  bool running = stepper.run();
  if (wasRunning && !running) {
    stepper.disableOutputs();          // move finished: release the coils
  }
  wasRunning = running;
}

bool isWatering() {
  return stepper.distanceToGo() != 0;
}