#include "main.h"
#include "auton.hpp"

bool debugMode = false;
bool kidMode = false;
bool autonChosen = false;

pros::Motor launcher_motor(LAUNCHER_PORT);

pros::Controller master(CONTROLLER_MASTER);
pros::Controller partner(CONTROLLER_PARTNER);

void update_lcd() {
    if(autonChosen == false) {
        autonPrint();
    }
    else {
        pros::lcd::clear_line(2);
        pros::lcd::set_text(2, "Debug Mode   Kid Mode   Auton Mode");    }
}

void on_left_button() {
    if(autonChosen == false) {
        swapAuton(-1);
    }
}
void on_center_button() {
    pros::lcd::clear_line(2);
    /*
	if (debugMode == false) {
        pros::lcd::clear_line(2);
		pros::lcd::set_text(2, "Debug Mode Enabled");
        debugMode = true;
	} else {
		pros::lcd::clear_line(2);
        pros::lcd::set_text(2, "Debug Mode Disabled");
        debugMode = false;
	}
    */
}
void on_right_button() {
    if(autonChosen == false) {
        swapAuton(1);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    std::cout << "Init" << std::endl;
	pros::lcd::initialize();
    std::cout << "Screen Init" << std::endl;
	pros::lcd::set_text(3, "9263A");
	//pros::lcd::register_btn0_cb(on_left_button);
	//pros::lcd::register_btn1_cb(on_center_button);
    //pros::lcd::register_btn2_cb(on_right_button);
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
    runAuton(1);
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
    while (true) {
        pros::lcd::set_text(3, "9263A");
        int power = (master.get_analog(ANALOG_LEFT_Y) * DEFAULT_SPEED);
        int strafe = (master.get_analog(ANALOG_RIGHT_X) * DEFAULT_SPEED);

		// Reset the power because it is set in multiple places
		setPowerVar(0, 0, 0, 0);
			
        setMotorsFromJoysticks(power, strafe);

        setMotorsFromDigitalButtons();

        // Set motor values based on individual axes if not already set
        if (frontLeftPower == 0 && backLeftPower == 0 && frontRightPower == 0 && backRightPower == 0) {
            setMotorsFromAxes(power, strafe);
        }

        updateMotors();

        if(debugMode == true) {
            driveDebug();
        }

        if(partner.get_digital(DIGITAL_L1)) {
            launcher_motor.move(50);
        } 
        else if (partner.get_digital(DIGITAL_L2)) {
            launcher_motor.move(-50);
        }
        else {
            launcher_motor.move(0);
        }
    }
}

void setMotorsFromJoysticks(int power, int strafe) {
    if (abs(power) > 0.2 && abs(strafe) > 0.2) {
        int move = abs(power) + abs(strafe);
        if (power > 0 && strafe > 0) {
            setPowerVar(move, 0, 0, -move);
        }
        else if (power > 0 && strafe < 0) {
            setPowerVar(0, move, -move, 0);
        }
        else if (power < 0 && strafe < 0) {
            setPowerVar(-move, 0, 0, move);
        }
        else if (power < 0 && strafe > 0) {
            setPowerVar(0, -move, move, 0);
        }
    }
}

void setMotorsFromDigitalButtons() {
    if (master.get_digital(DIGITAL_L1)) {
        setPowerVar(-100, -100, -100, -100);
    }
    else if (master.get_digital(DIGITAL_R1)) {
        setPowerVar(100, 100, 100, 100);
    }
    else if (master.get_digital(DIGITAL_L2)) {
        setPowerVar(-50, -50, -50, -50);
    }
    else if (master.get_digital(DIGITAL_R2)) {
        setPowerVar(50, 50, 50, 50);
    }
}

void setMotorsFromAxes(int power, int strafe) {
    if (abs(power) > 0.2) {
        setPowerVar(power, power, -power, -power);
    }
    else if (abs(strafe) > 0.2) {
        setPowerVar(strafe, -strafe, strafe, -strafe);
    }
}