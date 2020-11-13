#include "main.h"

pros::Controller master(CONTROLLER_MASTER);

void initialize() {
	selector::init();

	// subsystems
	chassis::init();
	intake::init();
	indexer::init();
	flywheel::init();
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
