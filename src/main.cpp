#include "main.h"

rd::Selector auton_selector("Auton Selector", {
	{"Positive Red", positive_red, "", 0},
	{"Negative Red", negative_red, "", 0},
	{"Positive Blue", positive_blue, "", 240},
	{"Negative Blue", negative_blue, "", 240},
});

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	auton_selector.focus();
	debug_console.print("Initializing... ");
	chassis.calibrate();
	debug_console.print("DONE\n");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

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
	debug_console.print("Running Auton...\n");
	auton_selector.run_auton();
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
	debug_console.print("Running Operator Control\n");
	while (true) {
		int throttle = controller.get_analog(ANALOG_LEFT_Y);
		int turn = controller.get_analog(ANALOG_RIGHT_X);
		
		chassis.curvature(throttle, turn);
		pros::delay(20);                               // Run for 20 ms then update
	}
}