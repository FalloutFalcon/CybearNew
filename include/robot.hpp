#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include "main.h"

bool debugMode = false;

// Constants for motor and controller ports
const int FRONT_LEFT_WHEEL_PORT = 1;
const int BACK_LEFT_WHEEL_PORT = 4;
const int FRONT_RIGHT_WHEEL_PORT = 2;
const int BACK_RIGHT_WHEEL_PORT = 3;

pros::Motor frontLeftMotor(FRONT_LEFT_WHEEL_PORT);
pros::Motor backLeftMotor(BACK_LEFT_WHEEL_PORT);
pros::Motor frontRightMotor(FRONT_RIGHT_WHEEL_PORT);
pros::Motor backRightMotor(BACK_RIGHT_WHEEL_PORT);

int frontLeftPower = 0;
int backLeftPower = 0;
int frontRightPower = 0;
int backRightPower = 0;

pros::Controller master(CONTROLLER_MASTER);

bool leftButton1 = false;
bool rightButton1 = false;
bool leftButton2 = false;
bool rightButton2 = false;

// Function prototypes
void setMotors(int power, int strafe);
void setMotorsFromDigitalButtons();
void setMotorsFromAxes(int power, int strafe);

// Auton
void moveFor(int time, char32_t direction, int speed = 100);
void setMove(int frontLeftMove, int backLeftMove, int frontRightMove, int backRightMove);

#endif // ROBOT_HPP_