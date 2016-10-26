/**
 * Robot Car
 * 
 * Testing motor control functionality
 */

#include "MotorController.h"

int velocity = 0;
int speed = 0;
boolean moveForward = true;
MOTOR_REF m1;

void setup() {
  Serial.begin(19200);
  motorInit(m1, 2, 3);
  printStats();
}

void loop() {
  if (speed > 0) {
    if (moveForward)
      motorForward(m1);
    else
      motorBackward(m1);
    delay(speed % 11);
  }
  motorStop(m1);
  delay(10 - (speed % 11));
}

void serialEvent() {
  while (Serial.available()) {
    int b = Serial.read();
    if (b == 'w' && velocity < 10)
      ++velocity;
    else if (b == 's' && velocity > -10)
      --velocity;
  }
  
  if (velocity >= 0) {
    moveForward = true;
    speed = velocity;
  } else {
    moveForward = false;
    speed = -1 * velocity;
  }

  printStats();
}

void printStats() {
  Serial.print("Current speed/direction: ");
  Serial.print(speed);
  Serial.println(moveForward ? "/forward" : "/reverse");
}

