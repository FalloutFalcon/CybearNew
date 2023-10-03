#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include "main.h"

// Constants for motor and controller ports
const int FRONT_LEFT_WHEEL_PORT = 1;
const int BACK_LEFT_WHEEL_PORT = 4;
const int FRONT_RIGHT_WHEEL_PORT = 2;
const int BACK_RIGHT_WHEEL_PORT = 3;

int frontLeftPower = 0;
int backLeftPower = 0;
int frontRightPower = 0;
int backRightPower = 0;

pros::Controller master(CONTROLLER_MASTER);

bool leftButton1 = master.get_digital(DIGITAL_L1);
bool rightButton1 = master.get_digital(DIGITAL_R1);
bool leftButton2 = master.get_digital(DIGITAL_L2);
bool rightButton2 = master.get_digital(DIGITAL_R2);

// Function prototypes
void setMotors(int power, int strafe);
void setMotorsFromDigitalButtons();
void setMotorsFromAxes(int power, int strafe);

#endif // ROBOT_HPP_