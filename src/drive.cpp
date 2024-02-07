#include "main.h"
#include "drive.hpp"

int frontLeftPower = 0;
int backLeftPower = 0;
int frontRightPower = 0;
int backRightPower = 0;

pros::Motor front_left_wheel(FRONT_LEFT_WHEEL_PORT);
pros::Motor back_left_wheel(BACK_LEFT_WHEEL_PORT);
pros::Motor front_right_wheel(FRONT_RIGHT_WHEEL_PORT);
pros::Motor back_right_wheel(BACK_RIGHT_WHEEL_PORT);

void setPowerVar(int frontLeftMove, int backLeftMove, int frontRightMove, int backRightMove)
{
    frontLeftPower = frontLeftMove;
    backLeftPower = backLeftMove;
    frontRightPower = frontRightMove;
    backRightPower = backRightMove;
}

void updateMotors()
{
    front_left_wheel.move(frontLeftPower);
    back_left_wheel.move(backLeftPower);
    front_right_wheel.move(frontRightPower);
    back_right_wheel.move(backRightPower);
}

void moveDir(int direction, int speed)
{
    switch (direction)
    {
    case NORTH: // Move forward
        setPowerVar(speed, speed, -speed, -speed);
        break;
    case SOUTH: // Move backward
        setPowerVar(-speed, -speed, speed, speed);
        break;
    case WEST: // Move left
        setPowerVar(-speed, speed, -speed, speed);
        break;
    case EAST: // Move right
        setPowerVar(speed, -speed, speed, -speed);
        break;
    case NORTHWEST: // Move diagonally up and left
        setPowerVar(0, speed, -speed, 0);
        break;
    case SOUTHWEST: // Move diagonally down and left
        setPowerVar(-speed, 0, 0, speed);
        break;
    case NORTHEAST: // Move diagonally up and right
        setPowerVar(speed, 0, 0, -speed);
        break;
    case SOUTHEAST: // Move diagonally down and right
        setPowerVar(0, -speed, speed, 0);
        break;
    case TURNLEFT: // Turn left
        setPowerVar(-speed, -speed, -speed, -speed);
        break;
    case TURNRIGHT: // Turn right
        setPowerVar(speed, speed, speed, speed);
        break;
    default:
        break;
    }
    updateMotors();
}

void moveFor(int time, int direction, int speed)
{
    moveDir(direction, speed);
    pros::delay(time);
    stopMotors();
}

void moveRelative(int frontLeftMove, int backLeftMove, int frontRightMove, int backRightMove, int speed)
{
    front_left_wheel.move_relative(frontLeftMove, speed);
    back_left_wheel.move_relative(backLeftMove, speed);
    front_right_wheel.move_relative(frontRightMove, speed);
    back_right_wheel.move_relative(backRightMove, speed);
}

void moveDistance(int distance, int direction, int speed)
{
    //((WHEEL_DIAMETER * PI * GEAR RATIO * RPM) / 60 SECONDS) / 12 INCHES)
    //diagonal feet / second.
    distance = ((distance / (WHEEL_DIAMETER * M_PI)) * GREEN_ENCODER_UNITS);
    double hypotenuse = std::sqrt(2 / std::pow(distance, 2));
    switch (direction)
    {
    case NORTH: // Move forward
        moveRelative(hypotenuse, hypotenuse, -hypotenuse, -hypotenuse, speed);
        break;
    case SOUTH: // Move backward
        moveRelative(-hypotenuse, -hypotenuse, hypotenuse, hypotenuse, speed);
        break;
    case WEST: // Move left
        moveRelative(-hypotenuse, hypotenuse, -hypotenuse, hypotenuse, speed);
        break;
    case EAST: // Move right
        moveRelative(hypotenuse, -hypotenuse, hypotenuse, -hypotenuse, speed);
        break;
    case NORTHWEST: // Move diagonally up and left
        moveRelative(0, distance, -distance, 0, speed);
        break;
    case SOUTHWEST: // Move diagonally down and left
        moveRelative(-distance, 0, 0, distance, speed);
        break;
    case NORTHEAST: // Move diagonally up and right
        moveRelative(distance, 0, 0, -distance, speed);
        break;
    case SOUTHEAST: // Move diagonally down and right
        moveRelative(0, -distance, distance, 0, speed);
        break;
    case TURNLEFT: // Turn left
        moveRelative(-distance, -distance, -distance, -distance, speed);
        break;
    case TURNRIGHT: // Turn right
        moveRelative(distance, distance, distance, distance, speed);
        break;
    default:
        break;
    }
}

void moveDistanceWhile(int distance, int direction, int speed)
{
    moveDistance(distance, direction, speed);
    do
    {
        pros::delay(10);
    } while (!allWheelsWithinTarget(5));
}

bool isWithinTarget(pros::Motor& wheel, double within) {
    double position = wheel.get_position();
    double target = wheel.get_target_position();
    return position + within > target && position - within < target;
}

bool allWheelsWithinTarget(double within) {
    return isWithinTarget(front_left_wheel, within) &&
           isWithinTarget(back_left_wheel, within) &&
           isWithinTarget(front_right_wheel, within) &&
           isWithinTarget(back_right_wheel, within);
}

void turnDegrees(int degrees, int speed)
{
    double distance = (degrees / 360) * (WHEEL_DIAMETER * M_PI);
    moveDistance(distance, TURNRIGHT, speed);
}

void stopMotors()
{
    setPowerVar(0, 0, 0, 0);
    updateMotors();
}

void driveDebug()
{
    int FLPos = front_left_wheel.get_position();
    int FLVolt = front_left_wheel.get_voltage();
    int FLTemp = front_left_wheel.get_temperature();
    pros::lcd::print(4, "FL pos:%d volt:%d temp:%d", FLPos, FLVolt, FLTemp);
    int BLPos = back_left_wheel.get_position();
    int BLVolt = back_left_wheel.get_voltage();
    int BLTemp = back_left_wheel.get_temperature();
    pros::lcd::print(5, "BL pos:%d volt:%d temp:%d", BLPos, BLVolt, BLTemp);
    int FRPos = front_right_wheel.get_position();
    int FRVolt = front_right_wheel.get_voltage();
    int FRTemp = front_right_wheel.get_temperature();
    pros::lcd::print(6, "FR pos:%d volt:%d temp:%d", FRPos, FRVolt, FRTemp);
    int BRPos = back_right_wheel.get_position();
    int BRVolt = back_right_wheel.get_voltage();
    int BRTemp = back_right_wheel.get_temperature();
    pros::lcd::print(7, "BR pos:%d volt:%d temp:%d", BRPos, BRVolt, BRTemp);
}
