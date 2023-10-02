#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

// Constants for motor and controller ports
const int FRONT_LEFT_WHEEL_PORT = 1;
const int BACK_LEFT_WHEEL_PORT = 2;
const int FRONT_RIGHT_WHEEL_PORT = 3;
const int BACK_RIGHT_WHEEL_PORT = 4;

// Function prototypes
void setMotors(int power, int strafe, int &FL, int &BL, int &FR, int &BR);
void setMotorsFromDigitalButtons(bool L1, bool R1, bool L2, bool R2, int &FL, int &BL, int &FR, int &BR);
void setMotorsFromAxes(int power, int strafe, int &FL, int &BL, int &FR, int &BR);

#endif // ROBOT_HPP_