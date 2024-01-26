#include "main.h"
#include "drive.hpp"
#include "auton.hpp"
#include "subsystems.hpp"

int scriptIndex = 0;

//So this creates a list of functions that can be called by index with the void type
std::function<void()> autonScripts[] = {
    testAuton,
    spinAuton,
    left1Auton,
    right1Auton,
    left2Auton,
    right2Auton
};

void swapAuton(int changeAmount) {
    scriptIndex = scriptIndex + changeAmount;
}

void runSelectedAuton() {
    runAuton(scriptIndex);
}

void runAuton(int auton) {
    autonScripts[auton]();
}

void autonPrint() {
    pros::lcd::clear_line(2);
    pros::lcd::set_text(2, "Auton: " + std::to_string(scriptIndex));
}

void testAuton() {
    while (true) {
        moveFor(1000, NORTH, 25);
        moveFor(1000, SOUTH, 25);
        moveFor(1000, EAST, 25);
        moveFor(1000, WEST, 25);
        moveFor(1000, NORTHWEST, 25);
        moveFor(1000, SOUTHWEST, 25);
        moveFor(1000, NORTHEAST, 25);
        moveFor(1000, NORTHWEST, 25);
        moveFor(1000, TURNLEFT, 25);
        moveFor(1000, TURNRIGHT, 25);
        stopMotors();
    }
}

void spinAuton() {
    moveDir(TURNLEFT, 10);
}

void left1Auton() {
    openPlough();
    moveFor(2000, NORTH, 25);
}

void right1Auton() {
    moveFor(1000, NORTH, 25);
}

void left2Auton() {
    moveFor(2000, NORTH, 25);
    moveFor(500, TURNLEFT, 25);
    releaseLauncher();
}

void right2Auton() {
    openPlough();
    moveFor(1000, NORTH, 25);
    moveFor(500, TURNRIGHT, 25);
    moveFor(1000, NORTH, 25);
    moveFor(50, TURNRIGHT, 25);
}