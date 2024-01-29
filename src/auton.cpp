#include "main.h"
#include "drive.hpp"
#include "auton.hpp"
#include "subsystems.hpp"

int scriptIndex = DEFAULT_AUTON_INDEX;

//So this creates a list of functions that can be called by index with the void type
std::function<void()> autonScripts[] = {
    testAuton,
    spinAuton,
    left1Auton,
    right1Auton,
    left2Auton,
    right2Auton,
    pushAuton
};

void swapAuton(int changeAmount) {
    scriptIndex = scriptIndex + changeAmount;
    autonPrint();
}

void runSelectedAuton() {
    runAuton(scriptIndex);
}

void runAuton(int auton) {
    autonScripts[auton]();
}

void autonPrint() {
    pros::lcd::set_text(1, "Auton: " + std::to_string(scriptIndex));
}

int currentAuton() {
    return scriptIndex;
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
    moveFor(500, NORTH, 127);
}

void right1Auton() {
    moveFor(500, NORTH, 75);
    moveFor(500, SOUTH, 75);
}

void left2Auton() {
    //windUpLauncher();
    //pros::delay(5000);
    windUpLauncher();
    //releaseLauncher();
}

void right2Auton() {
    openPlough();
    moveFor(1000, NORTH, 25);
    moveFor(500, TURNRIGHT, 25);
    moveFor(1000, NORTH, 25);
    moveFor(50, TURNRIGHT, 25);
}

void pushAuton() {
    moveFor(3500, NORTH, 75);
    moveFor(1000, SOUTH, 75);
}