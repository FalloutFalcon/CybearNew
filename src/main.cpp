#include "main.h"

#define FRONT_LEFT_WHEEL_PORT 1
#define BACK_LEFT_WHEEL_PORT 4
#define FRONT_RIGHT_WHEEL_PORT 2
#define BACK_RIGHT_WHEEL_PORT 3

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
  	pros::Controller master (CONTROLLER_MASTER);
	while(true) {

		int power  = master.get_analog(ANALOG_LEFT_Y);
		int strafe = master.get_analog(ANALOG_RIGHT_X);


	   	int FL = 0; 
   		int BL = 0;
   		int FR = 0;
   		int BR = 0;

		if (abs (power) > .2 & abs (strafe) > .2) {
			int move = abs (power) + abs (strafe);
			if (power > 0 & strafe > 0) {
				FL = move;
				BR = move * -1;
				
			}
			else if (power > 0 & strafe < 0) {
				BL = move;
   				FR = move * -1;

			}
			else if (power < 0 & strafe < 0) {
				FL = move * -1;
				BR = move;

			}
			else if (power < 0 & strafe > 0) {
				BL = move * -1;
   				FR = move;
			}
		}
		else if (master.get_digital(DIGITAL_L1)) {
			FL = -100;
   			BL = -100;
   			FR = -100;
   			BR = -100;
    	}
    	else if (master.get_digital(DIGITAL_R1)) {
			FL = 100;
   			BL = 100;
   			FR = 100;
   			BR = 100;
    	}
		else if (master.get_digital(DIGITAL_L2)) {
			FL = -50;
   			BL = -50;
   			FR = -50;
   			BR = -50;
    	}
    	else if (master.get_digital(DIGITAL_R2)) {
			FL = 50;
   			BL = 50;
   			FR = 50;
   			BR = 50;
    	}
		else if (abs (power) > .2) {
			FL = power; 
   			BL = power;
   			FR = power * -1;
   			BR = power * -1;
        }
		else if (abs (strafe) > .2) {
			FL = strafe; 
   			BL = strafe * -1;
   			FR = strafe;
   			BR = strafe * -1;
        }

   		front_left_wheel.move(FL);
   		back_left_wheel.move(BL);
   		front_right_wheel.move(FR);
   		back_right_wheel.move(BR);

		std::cout << FL;
		int FLVolt = front_left_wheel.get_voltage();
		int FLTemp = front_left_wheel.get_temperature();
		pros::lcd::print(1, "FL code:%d volt:%d temp:%d", FL, FLVolt, FLTemp ); 

	}

}