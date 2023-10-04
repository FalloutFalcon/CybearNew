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

// Drive Functions. Used in both Auton and Driver Control

// Sets the global motor power variables. Doesnt update motors on its own
void setPowerVar(int frontLeftMove, int backLeftMove, int frontRightMove, int backRightMove);
// Updates motors based on the global motor power variables. Should be called at the end of anything messing with motors and power varibles
void updateMotors();

// Driver Control Functions. Reads mostly controller inputs

// Set motor values based on joystick input
void setMotorsFromJoysticks(int power, int strafe);
// Set motor values based on digital button presses
void setMotorsFromDigitalButtons();
// Set motor values based on individual axes
void setMotorsFromAxes(int power, int strafe);

// Auton Control Functions. Related mostly to timing

// Uses moveDir to move in a direction for a specified time. Direction and speed are passed to moveDir. Time is in miliseconds
void moveFor(int time, char32_t direction, int speed = 50);
/**
 * Uses unicode to set the PowerVars to move in a direction with a set speed
 * \param speed
 *        Between -127 to 127. Defaults to 50
**/
void moveDir(char32_t direction, int speed);


#endif // ROBOT_HPP_