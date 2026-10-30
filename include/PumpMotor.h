#ifndef PUMP_MOTOR_H
#define PUMP_MOTOR_H

void initMotor();
void startWatering(long steps);   // queues one move of `steps`, returns immediately
void updateMotor();               // call on every loop pass
bool isWatering();                // true while the motor is still moving

#endif