#include "main.h"
#include "auton.hpp"

//So this creates a list of functions that can be called by index with the void type
std::function<void()> autonScripts[] = {
    testAuton,
    spinAuton
};

int scriptIndex = 0;

void swapAuton(int changeAmount) {
    scriptIndex = scriptIndex + changeAmount;
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
    moveDir(TURNLEFT, 25);
}

