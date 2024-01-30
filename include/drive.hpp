#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

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
void moveFor(int time, int direction = NORTH, int speed = 50);
/**
 * Uses unicode to set the PowerVars to move in a direction with a set speed
 * \param speed
 *        Between -127 to 127. Defaults to 50
**/
void moveDir(int direction = NORTH, int speed = 50);

void moveRelative(int distance, int speed = 50);
void moveDistance(int distance, int direction = NORTH, int speed = 50);
// Stops all motors and clears any loose power variables
void stopMotors();
// Prints alot of debug info for the drive train
void driveDebug();

#endif // DRIVE_HPP_