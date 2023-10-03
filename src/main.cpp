#include "robot.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	if (debugMode == false) {
        pros::lcd::clear_line(2);
		pros::lcd::set_text(2, "Debug Mode Enabled");
        debugMode = true;
	} else {
		pros::lcd::clear_line(2);
        pros::lcd::set_text(2, "Debug Mode Disabled");
        debugMode = false;
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "9263A");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    debugMode = false;
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    moveFor(1000, U'↑');
    moveFor(1000, U'↓');
    moveFor(1000, U'←');
    moveFor(1000, U'→');
    moveFor(1000, U'↖');
    moveFor(1000, U'↙');
    moveFor(1000, U'↗');
    moveFor(1000, U'↘');
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    pros::Motor front_left_wheel(FRONT_LEFT_WHEEL_PORT);
    pros::Motor back_left_wheel(BACK_LEFT_WHEEL_PORT);
    pros::Motor front_right_wheel(FRONT_RIGHT_WHEEL_PORT);
    pros::Motor back_right_wheel(BACK_RIGHT_WHEEL_PORT);

    while (true) {
        int power = master.get_analog(ANALOG_LEFT_Y);
        int strafe = master.get_analog(ANALOG_RIGHT_X);

		// Used to set the power of motors
		frontLeftPower = 0;
		backLeftPower = 0;
		frontRightPower = 0;
		backRightPower = 0;
			
		// Used to check digital button states
		leftButton1 = master.get_digital(DIGITAL_L1);
		rightButton1 = master.get_digital(DIGITAL_R1);
		leftButton2 = master.get_digital(DIGITAL_L2);
		rightButton2 = master.get_digital(DIGITAL_R2);

        // Function to set motor values based on joystick input
        setMotors(power, strafe);

        // Function to set motor values based on digital button presses
        setMotorsFromDigitalButtons();

        // Set motor values based on individual axes if not already set
        if (frontLeftPower == 0 && backLeftPower == 0 && frontRightPower == 0 && backRightPower == 0) {
            setMotorsFromAxes(power, strafe);
        }

        // Move motors
        front_left_wheel.move(frontLeftPower);
        back_left_wheel.move(backLeftPower);
        front_right_wheel.move(frontRightPower);
        back_right_wheel.move(backRightPower);

        // Output debugging information
        if(debugMode == true) {
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
    }
}

// Function to set motor values based on joystick input
void setMotors(int power, int strafe) {
    if (abs(power) > 0.2 && abs(strafe) > 0.2) {
        int move = abs(power) + abs(strafe);
        if (power > 0 && strafe > 0) {
            setMove(move, 0, 0, -move);
        }
        else if (power > 0 && strafe < 0) {
            setMove(0, move, -move, 0);
        }
        else if (power < 0 && strafe < 0) {
            setMove(-move, 0, 0, move);
        }
        else if (power < 0 && strafe > 0) {
            setMove(0, -move, move, 0);
        }
    }
}

// Function to set motor values based on digital button presses
void setMotorsFromDigitalButtons() {
    if (leftButton1) {
        setMove(-100, -100, -100, -100);
    }
    else if (rightButton1) {
        setMove(100, 100, 100, 100);
    }
    else if (leftButton2) {
        setMove(-50, -50, -50, -50);
    }
    else if (rightButton2) {
        setMove(50, 50, 50, 50);
    }
}

void setMotorsFromAxes(int power, int strafe) {
    if (abs(power) > 0.2) {
        setMove(power, power, -power, -power);
    }
    else if (abs(strafe) > 0.2) {
        setMove(strafe, -strafe, strafe, -strafe);
    }
}

#include "main.h"

void moveFor(int time, char32_t direction, int speed) {
    switch (direction) {
        case U'↑': // Move forward
            setMove(speed, speed, -speed, -speed);
            break;
        case U'↓': // Move backward
            setMove(-speed, -speed, speed, speed);
            break;
        case U'←': // Move left
            setMove(-speed, speed, -speed, speed);
            break;
        case U'→': // Move right
            setMove(speed, -speed, speed, -speed);
            break;
        case U'↖': // Move diagonally up and left
            setMove(0, speed, -speed, 0);
            break;
        case U'↙': // Move diagonally down and left
            setMove(-speed, 0, 0, -speed);
            break;
        case U'↗': // Move diagonally up and right
            setMove(speed, 0, 0, speed);
            break;
        case U'↘': // Move diagonally down and right
            setMove(0, -speed, speed, 0);
            break;
        default:
            break;
    }

    // Set motor values
    pros::Motor frontLeftMotor(FRONT_LEFT_WHEEL_PORT);
    pros::Motor backLeftMotor(BACK_LEFT_WHEEL_PORT);
    pros::Motor frontRightMotor(FRONT_RIGHT_WHEEL_PORT);
    pros::Motor backRightMotor(BACK_RIGHT_WHEEL_PORT);

    frontLeftMotor.move(frontLeftPower);
    backLeftMotor.move(backLeftPower);
    frontRightMotor.move(frontRightPower);
    backRightMotor.move(backRightPower);

    // Wait for specified time
    pros::delay(time);

    // Stop motors
    setMove(0, 0, 0, 0);
}

// Sets the power varibles to shrink code alot
void setMove(int frontLeftMove, int backLeftMove, int frontRightMove, int backRightMove) {
    frontLeftPower = frontLeftMove;
    backLeftPower = backLeftMove;
    frontRightPower = frontRightMove;
    backRightPower = backRightMove;
}

