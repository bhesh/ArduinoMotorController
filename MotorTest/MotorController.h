#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <stdint.h>

struct PIN_REF {
	volatile uint8_t *ddr;
	volatile uint8_t *port;
	uint8_t mask;
};

struct MOTOR_REF {
	PIN_REF pos;
	PIN_REF neg;
};

int motorInit(MOTOR_REF &ref, int pos_pin, int neg_pin);
int motorDel(MOTOR_REF &ref);
int motorForward(MOTOR_REF &ref);
int motorBackward(MOTOR_REF &ref);
int motorStop(MOTOR_REF &ref);

#endif
