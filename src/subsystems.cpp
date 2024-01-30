#include "main.h"

pros::Motor launcher_motor(LAUNCHER_PORT, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);
pros::Motor climb_motor(CLIMB_PORT);
pros::Motor plough_motor(PLOUGH_PORT);

int launcher_speed = 127;

void moveLauncher(int power)
{
    launcher_motor.move(power);
}

void breakLauncher()
{
    launcher_motor.brake();
}

void windUpLauncher()
{
    launcher_motor.move_relative(-340, launcher_speed);
}

void releaseLauncher()
{
    launcher_motor.move_relative(-20, launcher_speed);
}

void movePlough(int power)
{
    plough_motor.move(power);
}

void openPlough()
{
    plough_motor.move(127);
    // plough_motor.move_absolute(900, 100);
}

void closePlough()
{
    plough_motor.move(-127);
    // plough_motor.move_absolute(0, 100);
}

void subSystemDebug()
{
    int launcherVolt = launcher_motor.get_voltage();
    int launcherTemp = launcher_motor.get_temperature();
    int launcherPos = launcher_motor.get_position();
    pros::lcd::print(3, "Launcher pos:%d volt:%d temp:%d", launcherPos, launcherVolt, launcherTemp);
    std::cout << "Launcher pos: " << launcherPos << " volt: " << launcherVolt << " temp: " << launcherTemp << std::endl;
}
