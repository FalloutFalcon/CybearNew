#include "main.h"

pros::Motor launcher_motor(LAUNCHER_PORT, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);
pros::Motor climb_motor(CLIMB_PORT);
pros::Motor plough_motor(PLOUGH_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

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
    launcher_motor.move_relative(-332, launcher_speed);
}

void releaseLauncher()
{
    launcher_motor.move_relative(-28, launcher_speed);
}

// put the launcher to the number where  # % 360 = 0
void resetLauncher()
{
    double launcherPos = launcher_motor.get_position();
    int launcherPosMod = (int)launcherPos % 360;
    if (launcherPosMod < 0)
    {
        launcher_motor.move_relative(-launcherPosMod, launcher_speed);
    }
    else
    {
        launcher_motor.move_relative(360 - launcherPosMod, launcher_speed);
    }
}

void autoLaunch()
{
    isLaunching = true;
    windUpLauncher();
    pros::delay(750);
    releaseLauncher();
    pros::delay(500);
    isLaunching = false;
}

void movePlough(int power)
{
    plough_motor.move(power);
}

void openPlough()
{
    // plough_motor.move(127);
    plough_motor.move_absolute(-90, 100);
}

void closePlough()
{
    // plough_motor.move(-127);
    plough_motor.move_absolute(0, 100);
}

void fowardPlough()
{
    plough_motor.move_absolute(-180, 100);
}

void subSystemDebug()
{
    int launcherVolt = launcher_motor.get_voltage();
    int launcherTemp = launcher_motor.get_temperature();
    int launcherPos = launcher_motor.get_position();
    pros::lcd::print(3, "Launcher pos:%d volt:%d temp:%d", launcherPos, launcherVolt, launcherTemp);
    std::cout << "Launcher pos: " << launcherPos << " volt: " << launcherVolt << " temp: " << launcherTemp << std::endl;
}
