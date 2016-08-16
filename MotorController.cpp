/**
 * Motor Controller Functions
 */

#include "MotorController.h"

#include <Arduino.h>

#define MOTOR_A_P 0b00000100
#define MOTOR_A_N 0b00001000
#define MOTOR_B_P 0b00010000
#define MOTOR_B_N 0b00100000

#define MOTOR_STOP(PORT, P, N) (PORT & ~(P | N))
#define MOTOR_FORWARD(PORT, P, N) ((PORT & ~N) | P)
#define MOTOR_REVERSE(PORT, P, N) ((PORT & ~P) | N)

void initMotorControlPins() {
  DDRD = DDRD | (MOTOR_A_P | MOTOR_A_N | MOTOR_B_P | MOTOR_B_N);
}

void motorAStop() {
  PORTD = MOTOR_STOP(PORTD, MOTOR_A_P, MOTOR_A_N);
}

void motorAForward() {
  PORTD = MOTOR_FORWARD(PORTD, MOTOR_A_P, MOTOR_A_N);
}

void motorAReverse() {
  PORTD = MOTOR_REVERSE(PORTD, MOTOR_A_P, MOTOR_A_N);
}

void motorBStop() {
  PORTD = MOTOR_STOP(PORTD, MOTOR_B_P, MOTOR_B_N);
}

void motorBForward() {
  PORTD = MOTOR_FORWARD(PORTD, MOTOR_B_P, MOTOR_B_N);
}

void motorBReverse() {
  PORTD = MOTOR_REVERSE(PORTD, MOTOR_B_P, MOTOR_B_N);
}
