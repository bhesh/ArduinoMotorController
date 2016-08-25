#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

void initMotorControlPins();
void motorAStop();
void motorAForward();
void motorAReverse();
void motorBStop();
void motorBForward();
void motorBReverse();

struct PIN_REF {
	unsigned char *ddr;
	unsigned char *port;
	unsigned char mask;
};

struct MOTOR_REF {
	PIN_REF pos;
	PIN_REF neg;
};

int initMotor(MOTOR_REF &ref, int pos_pin, int neg_pin);
int forward(MOTOR_REF &ref);
int backward(MOTOR_REF &ref);
int stop(MOTOR_REF &ref);

#endif
