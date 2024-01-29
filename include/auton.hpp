#ifndef _AUTON_HPP_
#define _AUTON_HPP_

#define DEFAULT_AUTON_INDEX 0
#define TEST_AUTON 0
#define SPIN_AUTON 1
#define LEFT1_AUTON 2
#define RIGHT1_AUTON 3
#define LEFT2_AUTON 4
#define RIGHT2_AUTON 5
#define PUSH_AUTON 6

void swapAuton(int changeAmount);
void runSelectedAuton();
void runAuton(int auton);
void autonPrint();
int currentAuton();

void testAuton();
void spinAuton();

void left1Auton();
void right1Auton();

void left2Auton();
void right2Auton();

void pushAuton();

#endif // AUTON_HPP_