/**
 * Motor Controller Functions
 */

#include "MotorController.h"

#include <Arduino.h>

#define GET_DDR(P) ((P >= 2 && P <= 7) ? &DDRD : (P >= 8 && P <= 13) ? &DDRB : 0)
#define GET_PORT(P) ((P >= 2 && P <= 7) ? &PORTD : (P >= 8 && P <= 13) ? &PORTB : 0)
#define GET_MASK(P) (1 << (P % 8))
#define PIN_ON(PORT, M) (PORT | M)
#define PIN_OFF(PORT, M) (PORT & ~M)

/**
 * Initialize the motor pins
 *
 * Returns 0 on success, -1 on error
 */
int initMotor(MOTOR_REF &ref, int pos_pin, int neg_pin) {

	// Get positive pin info
	ref.pos.ddr = GET_DDR(pos_pin);
	ref.pos.port = GET_PORT(pos_pin);
	ref.pos.mask = GET_MASK(pos_pin);

	// Get negative pin info
	ref.neg.ddr = GET_DDR(neg_pin);
	ref.neg.port = GET_PORT(neg_pin);
	ref.neg.mask = GET_MASK(neg_pin);

	// Initialize pins
	if (ref.pos.ddr == 0 || ref.pos.port == 0 || ref.neg.ddr == 0 || ref.neg.port == 0)
		return -1;
	*ref.pos.ddr = PIN_ON(*ref.pos.ddr, ref.pos.mask);
	*ref.neg.ddr = PIN_ON(*ref.neg.ddr, ref.neg.mask);
	return 0;
}

/**
 * Unsets the motor pins
 *
 * Returns 0 on success, -1 on error
 */
int delMotor(MOTOR_REF &ref) {
	if (ref.pos.ddr == 0 || ref.pos.port == 0 || ref.neg.ddr == 0 || ref.neg.port == 0)
		return -1;
	*ref.pos.port = PIN_OFF(*ref.pos.port, ref.pos.mask);
	*ref.neg.port = PIN_OFF(*ref.neg.port, ref.neg.mask);
	*ref.pos.ddr = PIN_OFF(*ref.pos.ddr, ref.pos.mask);
	*ref.neg.ddr = PIN_OFF(*ref.neg.ddr, ref.neg.mask);
	return 0;
}

/**
 * Drives the motor forward
 *
 * Returns 0 on success, -1 on error
 */
int forward(MOTOR_REF &ref) {
	if (ref.pos.port == 0 || ref.neg.port == 0)
		return -1;
	*ref.pos.port = PIN_ON(*ref.pos.port, ref.pos.mask);
	*ref.neg.port = PIN_OFF(*ref.neg.port, ref.neg.mask);
	return 0;
}

/**
 * Drives the motor backwards
 *
 * Returns 0 on success, -1 on error
 */
int backward(MOTOR_REF &ref) {
	if (ref.pos.port == 0 || ref.neg.port == 0)
		return -1;
	*ref.pos.port = PIN_OFF(*ref.pos.port, ref.pos.mask);
	*ref.neg.port = PIN_ON(*ref.neg.port, ref.neg.mask);
	return 0;
}

/**
 * Stops the motor
 *
 * Returns 0 on success, -1 on error
 */
int stop(MOTOR_REF &ref) {
	if (ref.pos.port == 0 || ref.neg.port == 0)
		return -1;
	*ref.pos.port = PIN_OFF(*ref.pos.port, ref.pos.mask);
	*ref.neg.port = PIN_OFF(*ref.neg.port, ref.neg.mask);
	return 0;
}

/**
 * OLD CODE BELOW FOR BACKWARDS COMPATIBILITY
 */

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
