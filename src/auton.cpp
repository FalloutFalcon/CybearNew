#include "main.h"
#include "drive.hpp"
#include "auton.hpp"
#include "subsystems.hpp"

int currentAutonIndex = DEFAULT_AUTON_INDEX;

// So this creates a list of functions that can be called by index with the void type
std::function<void()> autonScripts[] = {
    testAuton,
    spinAuton,
    left1Auton,
    right1Auton,
    left2Auton,
    right2Auton,
    pushAuton};

std::vector<std::string> autonNames = {
    "Test Auton",
    "Spin Auton",
    "Left1 Auton",
    "Right1 Auton",
    "Left2 Auton",
    "Right2 Auton",
    "Push Auton"
};

void swapAuton(int changeAmount)
{
    if (currentAutonIndex + changeAmount > 0 && currentAutonIndex + changeAmount < sizeof(autonScripts))
    {
         currentAutonIndex = currentAutonIndex + changeAmount;
    }
    else
    {
        currentAutonIndex = 0;
    }
    autonPrint();
}

void runSelectedAuton()
{
    runAuton(currentAutonIndex);
}

void runAuton(int auton)
{
    autonScripts[auton]();
}

void autonPrint()
{
    pros::lcd::set_text(1, "Auton: " + autonToString(currentAutonIndex));
}

std::string autonToString(int autonIndex)
{
    std::string stringIndex = "Nothing?";
    if (autonIndex >= 0 && autonIndex < autonNames.size())
    {
        stringIndex = autonNames[autonIndex];
    }
    return stringIndex;
}

int currentAuton()
{
    return currentAutonIndex;
}

void testAuton()
{
    moveDistanceWhile(6, NORTHWEST, 50);
    /*
    while (true)
    {   
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
    */
}

void spinAuton()
{
    moveDir(TURNLEFT, 10);
}

void left1Auton()
{
    moveFor(500, NORTH, 127);
}

void right1Auton()
{
    moveFor(500, NORTH, 75);
    moveFor(500, SOUTH, 75);
}

void left2Auton()
{
    // windUpLauncher();
    // pros::delay(5000);
    windUpLauncher();
    // releaseLauncher();
}

void right2Auton()
{
    openPlough();
    moveFor(1000, NORTH, 25);
    moveFor(500, TURNRIGHT, 25);
    moveFor(1000, NORTH, 25);
    moveFor(50, TURNRIGHT, 25);
}

void pushAuton()
{
    moveFor(3500, NORTH, 75);
    moveFor(1000, SOUTH, 75);
}