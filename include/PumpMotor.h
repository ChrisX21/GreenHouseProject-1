#ifndef PUMP_MOTOR_H
#define PUMP_MOTOR_H

void initMotor();
void startWatering();    // starts one move, returns immediately
void updateMotor();      // call on every loop pass
bool isWatering();       // true while the motor is still moving

#endif