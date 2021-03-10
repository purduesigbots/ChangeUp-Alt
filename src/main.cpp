#include "main.h"
#include "subsystems/flywheel.hpp"
#include "subsystems/intake.hpp"

pros::Controller master(CONTROLLER_MASTER);

int controllerTaskFn() {
	while (1) {
		// master.clear_line(2);
		// delay(50);
		flywheel::setState(1);
		printf("%d", flywheel::getState());
		delay(100);
	}
}

void initialize() {
	selector::init();

	chassis::init({-12, -13}, {9, 1}, // motors
	              600,                // gearset
	              41.45, 1,           // TPU
	              7,                  // setle time
	              9, 5,               // linear/angular thresholds
	              2, 2,               // regular/arc slew
	              8,                  // imu port
	              {0, 0, 0},          // encoder ports
	              0,                  // expander port
	              10                  // joystick threshold
	);
	odom::init(false, // debug output
	           7.825, // left/right distance
	           7.825, // middle distance
	           69.44, // left/right tpi
	           69.44, // middle tpi
	           true,  // holonomic enabled
	           2      // exit error

	);
	pid::init(false,  // debug output
	          .3, .5, // linear constants
	          1.4, 3, // angular contants
	          4, 0,   // linear point constants
	          50, 0,  // angular point constants
	          .05,    // arc kp
	          .5,     // dif kp
	          10      // min error
	);

	// subsystems
	intake::init();
	indexer::init();
	flywheel::init();
	vision::init();
	sensors::init();

	// Task controllerTask(controllerTaskFn);
}

void disabled() {
}

void competition_initialize() {
}

void autonomous() {
	switch (selector::auton) {
	case -1:
		blue();
		break;
	case 1:
		red();
		break;
	case 0:
		skills();
		break;
	}
}

void opcontrol() {
	while (true) {

		// button to start autonomous for testing
		if (master.get_digital(DIGITAL_LEFT) && !competition::is_connected())
			autonomous();

		// intake
		intake::opcontrol();

		// indexer
		indexer::opcontrol();

		// flywheel
		flywheel::opcontrol();

		// chassis
		chassis::holonomic(master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		                   master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127,
		                   master.get_analog(ANALOG_LEFT_X) * (double)100 / 127);

		// deploy macro
		if (master.get_digital(DIGITAL_A)) {
			intake::move(100);
			indexer::move(100);
			flywheel::move(-100);
		}

		delay(20);
	}
}
