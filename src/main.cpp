#include "main.h"

pros::Controller master(CONTROLLER_MASTER);

void initialize() {
	selector::init();

	chassis::init({-14, -13}, {3, 1}, // motors
	              600,                // gearset
	              41.45, 2.3,         // TPU
	              5,                  // setle time
	              1, 1,               // linear/angular thresholds
	              8, 2,               // regular/arc slew
	              0,                  // imu port
	              {0, 0, 0},          // encoder ports
	              0,                  // expander port
	              10                  // joystick threshold
	);
	odom::init(false, // debug output
	           7.625, // left/right distance
	           7.625, // middle distance
	           69.44, // left/right tpi
	           69.44, // middle tpi
	           true   // holonomic enabled
	);
	pid::init(false,  // debug output
	          .3, .5, // linear constants
	          .8, 3,  // angular contants
	          .05,    // arc kp
	          .5,     // dif kp
	          4, 0,   // linear point constants
	          35, 0,  // angular point constants
	          5       // min error
	);

	// subsystems
	intake::init();
	indexer::init();
	flywheel::init();
	vision::init();
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

		delay(20);
	}
}
