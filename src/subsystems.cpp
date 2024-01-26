#include "main.h"

pros::Motor launcher_motor(LAUNCHER_PORT);
pros::Motor climb_motor(CLIMB_PORT);
pros::Motor plough_motor(PLOUGH_PORT);

void moveLauncher(int power) {
    launcher_motor.move(power);
}

void windUpLauncher() {
    launcher_motor.move_absolute(-900, 25);
}

void releaseLauncher() {
    launcher_motor.move_absolute(0, 25);
}

void movePlough(int power) {
    plough_motor.move(power);
}

void openPlough() {
    plough_motor.move(127);
    //plough_motor.move_absolute(900, 100);
}

void closePlough() {
    plough_motor.move(-127);
    //plough_motor.move_absolute(0, 100);
}

void subSystemDebug() {
    int launcherVolt = launcher_motor.get_voltage();
    int launcherTemp = launcher_motor.get_temperature();
    int launcherPos = launcher_motor.get_position();
    pros::lcd::print(2, "Launcher pos:%d volt:%d temp:%d", launcherPos, launcherVolt, launcherTemp);
    std::cout << "Launcher pos: " << launcherPos << " volt: " << launcherVolt << " temp: " << launcherTemp << std::endl;
    
    int ploughVolt = plough_motor.get_voltage();
    int ploughTemp = plough_motor.get_temperature();
    int ploughPos = plough_motor.get_position();
    pros::lcd::print(3, "Plough pos:%d volt:%d temp:%d", ploughPos, ploughVolt, ploughTemp);
    std::cout << "Plough pos: " << ploughPos << " volt: " << ploughVolt << " temp: " << ploughTemp << std::endl;
}
