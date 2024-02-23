#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

extern bool debugMode;
extern bool kidMode;
extern bool autonChosen;
extern bool isLaunching;

// Multiplication for the drive speed. Useful for creating kid safe versions for demos
const int DEFAULT_SPEED = 1;

// Constants for motor and controller ports
const int FRONT_LEFT_WHEEL_PORT = 1;
const int BACK_LEFT_WHEEL_PORT = 4;
const int FRONT_RIGHT_WHEEL_PORT = 2;
const int BACK_RIGHT_WHEEL_PORT = 3;
const int LAUNCHER_PORT = 5;
const int CLIMB_PORT = 6;
const int PLOUGH_PORT = 7;

#define RED_ENCODER_UNITS 745
#define GREEN_ENCODER_UNITS 900

//Inches
#define WHEEL_DIAMETER 4

#define NORTH 1
#define SOUTH 2
#define EAST 4
#define WEST 8
#define NORTHEAST 5  //(1 + 4)
#define SOUTHEAST 6  //(2 + 4)
#define NORTHWEST 9  //(1 + 8)
#define SOUTHWEST 10 //(2 + 8)
#define TURNLEFT 13
#define TURNRIGHT 14
// Driver Control Functions. Reads mostly controller inputs

// Set motor values based on joystick input
void setMotorsFromJoysticks(int power, int strafe);
// Set motor values based on digital button presses
void setMotorsFromDigitalButtons();
// Set motor values based on individual axes
void setMotorsFromAxes(int power, int strafe);

void printingInfo(void* param);

#endif // ROBOT_HPP_