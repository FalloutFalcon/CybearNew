#include "robot.hpp"

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
        std::cout << frontLeftPower;
        int FLVolt = front_left_wheel.get_voltage();
        int FLTemp = front_left_wheel.get_temperature();
        pros::lcd::print(1, "FL code:%d volt:%d temp:%d", frontLeftPower, FLVolt, FLTemp);
    }
}

// Function to set motor values based on joystick input
void setMotors(int power, int strafe) {
    if (abs(power) > 0.2 && abs(strafe) > 0.2) {
        int move = abs(power) + abs(strafe);
        if (power > 0 && strafe > 0) {
            frontLeftPower = move;
            backRightPower = -move;
        }
        else if (power > 0 && strafe < 0) {
            backLeftPower = move;
            frontRightPower = -move;
        }
        else if (power < 0 && strafe < 0) {
            frontLeftPower = -move;
            backRightPower = move;
        }
        else if (power < 0 && strafe > 0) {
            backLeftPower = -move;
            frontRightPower = move;
        }
    }
}

// Function to set motor values based on digital button presses
void setMotorsFromDigitalButtons() {
    if (leftButton1) {
        frontLeftPower = -100;
        backLeftPower = -100;
        frontRightPower = -100;
        backRightPower = -100;
    }
    else if (rightButton1) {
        frontLeftPower = 100;
        backLeftPower = 100;
        frontRightPower = 100;
        backRightPower = 100;
    }
    else if (leftButton2) {
        frontLeftPower = -50;
        backLeftPower = -50;
        frontRightPower = -50;
        backRightPower = -50;
    }
    else if (rightButton2) {
        frontLeftPower = 50;
        backLeftPower = 50;
        frontRightPower = 50;
        backRightPower = 50;
    }
}

// Function to set motor values based on individual axes
void setMotorsFromAxes(int power, int strafe) {
    if (abs(power) > 0.2) {
        frontLeftPower = power;
        backLeftPower = power;
        frontRightPower = -power;
        backRightPower = -power;
    }
    else if (abs(strafe) > 0.2) {
        frontLeftPower = strafe;
        backLeftPower = -strafe;
        frontRightPower = strafe;
        backRightPower = -strafe;
    }
}
