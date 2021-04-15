#include "main.h"
#include "ARMS/odom.h"
#include "subsystems/flywheel.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/sensors.hpp"

pros::Controller master(CONTROLLER_MASTER);

int controllerTaskFn() {
	while (1) {
		// master.clear_line(2);
		// delay(50);
		// flywheel::setState(1);
		master.clear_line(3);
		delay(50);
		master.print(3, 1, "%.2lf %.2lf %.2lf", odom::global_x, odom::global_y,
		             odom::heading_degrees);
		delay(50);
	}
}

void initialize() {
	selector::init();

	chassis::init({-12, -1}, {9, 7}, // motors
	              600,               // gearset
	              41.45, 1,          // TPU
	              12,                // setle time
	              6, 5,              // linear/angular thresholds
	              2, 2,              // regular/arc slew
	              8,                 // imu port
	              {0, 0, 0},         // encoder ports
	              0,                 // expander port
	              10                 // joystick threshold
	);
	odom::init(true,  // debug output
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
	          15, 25, // linear point constants
	          50, 0,  // angular point constants
	          .5,     // arc kp
	          0,      // dif kp
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

		// ejector
		ejector::opcontrol();

		// flywheel
		flywheel::opcontrol();

		// chassis
		chassis::holonomic(master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		                   master.get_analog(ANALOG_LEFT_X) * (double)100 / 127,
		                   master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127);

		// deploy macro
		if (master.get_digital(DIGITAL_A)) {
			intake::move(100);
			indexer::move(100);
			flywheel::move(-70);
		}

		// ultrasonic debugging
		// std::array<double, 2> offsets = sensors::get_xy_offset(0);
		// printf("%.2lf,%.2lf\n", offsets[0], offsets[1]);

		delay(20);
	}
}
