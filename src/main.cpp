#include "main.h"
#include "robot.hpp"

using namespace okapi;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
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
	pros::lcd::set_text(1, "Hello PROS User!");

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
void competition_initialize() {}

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
void autonomous() {}

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
    pros::Controller master(CONTROLLER_MASTER);

    while (true) {
        int power = master.get_analog(ANALOG_LEFT_Y);
        int strafe = master.get_analog(ANALOG_RIGHT_X);

		// Used to set the power of motors
        int FL = 0;
        int BL = 0;
        int FR = 0;
        int BR = 0;
		
		// Used to check digital button states
		bool L1 = master.get_digital(DIGITAL_L1);
        bool R1 = master.get_digital(DIGITAL_R1);
        bool L2 = master.get_digital(DIGITAL_L2);
        bool R2 = master.get_digital(DIGITAL_R2);

        // Function to set motor values based on joystick input
        setMotors(power, strafe, FL, BL, FR, BR);

        // Function to set motor values based on digital button presses
        setMotorsFromDigitalButtons(L1, R2, L2, R2, FL, BL, FR, BR);

        // Set motor values based on individual axes if not already set
        if (FL == 0 && BL == 0 && FR == 0 && BR == 0) {
            setMotorsFromAxes(power, strafe, FL, BL, FR, BR);
        }

        // Move motors
        front_left_wheel.move(FL);
        back_left_wheel.move(BL);
        front_right_wheel.move(FR);
        back_right_wheel.move(BR);

        // Output debugging information
        std::cout << FL;
        int FLVolt = front_left_wheel.get_voltage();
        int FLTemp = front_left_wheel.get_temperature();
        pros::lcd::print(1, "FL code:%d volt:%d temp:%d", FL, FLVolt, FLTemp);
    }
}

// Function to set motor values based on joystick input
void setMotors(int power, int strafe, int &FL, int &BL, int &FR, int &BR) {
    if (abs(power) > 0.2 && abs(strafe) > 0.2) {
        int move = abs(power) + abs(strafe);
        if (power > 0 && strafe > 0) {
            FL = move;
            BR = -move;
        }
        else if (power > 0 && strafe < 0) {
            BL = move;
            FR = -move;
        }
        else if (power < 0 && strafe < 0) {
            FL = -move;
            BR = move;
        }
        else if (power < 0 && strafe > 0) {
            BL = -move;
            FR = move;
        }
    }
}

// Function to set motor values based on digital button presses
void setMotorsFromDigitalButtons(bool L1, bool R1, bool L2, bool R2, int &FL, int &BL, int &FR, int &BR) {
    if (L1) {
        FL = -100;
        BL = -100;
        FR = -100;
        BR = -100;
    }
    else if (R1) {
        FL = 100;
        BL = 100;
        FR = 100;
        BR = 100;
    }
    else if (L2) {
        FL = -50;
        BL = -50;
        FR = -50;
        BR = -50;
    }
    else if (R2) {
        FL = 50;
        BL = 50;
        FR = 50;
        BR = 50;
    }
}

// Function to set motor values based on individual axes
void setMotorsFromAxes(int power, int strafe, int &FL, int &BL, int &FR, int &BR) {
    if (abs(power) > 0.2) {
        FL = power;
        BL = power;
        FR = -power;
        BR = -power;
    }
    else if (abs(strafe) > 0.2) {
        FL = strafe;
        BL = -strafe;
        FR = strafe;
        BR = -strafe;
    }
}
