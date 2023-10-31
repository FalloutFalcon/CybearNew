#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"

extern int frontLeftPower;
extern int backLeftPower;
extern int frontRightPower;
extern int backRightPower;

// Drive Functions. Used in both Auton and Driver Control

// Sets the global motor power variables. Doesnt update motors on its own
void setPowerVar(int frontLeftMove, int backLeftMove, int frontRightMove, int backRightMove);
// Updates motors based on the global motor power variables. Should be called at the end of anything messing with motors and power varibles
void updateMotors();

// Auton Control Functions. Related mostly to timing

// Uses moveDir to move in a direction for a specified time. Direction and speed are passed to moveDir. Time is in miliseconds
void moveFor(int time, int direction, int speed = 50);
/**
 * Uses unicode to set the PowerVars to move in a direction with a set speed
 * \param speed
 *        Between -127 to 127. Defaults to 50
**/
void moveDir(int direction, int speed);
// Stops all motors and clears any loose power variables
void stopMotors();

void driveDebug();

#endif // DRIVE_HPP_