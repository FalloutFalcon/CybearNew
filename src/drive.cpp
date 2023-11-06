#include "main.h"

int frontLeftPower = 0;
int backLeftPower = 0;
int frontRightPower = 0;
int backRightPower = 0;

pros::Motor front_left_wheel(FRONT_LEFT_WHEEL_PORT);
pros::Motor back_left_wheel(BACK_LEFT_WHEEL_PORT);
pros::Motor front_right_wheel(FRONT_RIGHT_WHEEL_PORT);
pros::Motor back_right_wheel(BACK_RIGHT_WHEEL_PORT);

void setPowerVar(int frontLeftMove, int backLeftMove, int frontRightMove, int backRightMove) {
    frontLeftPower = frontLeftMove;
    backLeftPower = backLeftMove;
    frontRightPower = frontRightMove;
    backRightPower = backRightMove;
}

void updateMotors() {
    front_left_wheel.move(frontLeftPower);
    back_left_wheel.move(backLeftPower);
    front_right_wheel.move(frontRightPower);
    back_right_wheel.move(backRightPower);
}

void moveDir(int direction, int speed) {
    switch (direction) {
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

void moveFor(int time, int direction, int speed) {
    moveDir(time, direction);
    pros::delay(time);
    stopMotors();
}

void stopMotors() {
    setPowerVar(0, 0, 0, 0);
    updateMotors();
}

void driveDebug() {
    int FLVolt = front_left_wheel.get_voltage();
    int FLTemp = front_left_wheel.get_temperature();
    pros::lcd::print(3, "FL code:%d volt:%d temp:%d", frontLeftPower, FLVolt, FLTemp);
    int BLVolt = back_left_wheel.get_voltage();
    int BLTemp = back_left_wheel.get_temperature();
    pros::lcd::print(4, "BL code:%d volt:%d temp:%d", backLeftPower, BLVolt, BLTemp);
    int FRVolt = front_right_wheel.get_voltage();
    int FRTemp = front_right_wheel.get_temperature();
    pros::lcd::print(5, "FR code:%d volt:%d temp:%d", frontRightPower, FRVolt, FRTemp);
    int BRVolt = back_right_wheel.get_voltage();
    int BRTemp = back_right_wheel.get_temperature();
    pros::lcd::print(6, "BR code:%d volt:%d temp:%d", backRightPower, BRVolt, BRTemp);
}
