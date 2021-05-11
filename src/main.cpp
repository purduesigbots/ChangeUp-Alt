#include "main.h"

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

	chassis::init({-12, -1}, {6, 7}, // motors
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
	pid::init(false,     // debug output
	          .3, 0, .5, // linear constants
	          1.4, 0, 3, // angular contants
	          15, 0, 25, // linear point constants
	          50, 0, 0,  // angular point constants
	          .5,        // arc kp
	          0,         // dif kp
	          10         // min error
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
	bool intakes_open = false;
	while (true) {

		// button to start autonomous for testing
		if (master.get_digital(DIGITAL_LEFT) && !competition::is_connected())
			autonomous();

		// stop all subsystems
		intake::speed = 0;
		indexer::speed = 0;
		flywheel::speed = 0;
		ejector::speed = 0;
		intakes_open = false;

		// intake
		if (master.get_digital(DIGITAL_R1)) {
			intake::speed = 100;
			indexer::speed = 50;
			ejector::speed = 100;
		}

		// actuate
		if (master.get_digital(DIGITAL_R2)) {
			intakes_open = true;
		}

		// score
		if (master.get_digital(DIGITAL_L1)) {
			indexer::speed = 100;
			flywheel::speed = 100;
			ejector::speed = 100;
		}

		// eject from top
		if (master.get_digital(DIGITAL_L2)) {
			if (indexer::speed == 0)
				indexer::speed = -100;
			if (ejector::speed == 0)
				flywheel::speed = -100;
			ejector::speed = -100;
		}

		// eject from bottom
		if (master.get_digital(DIGITAL_X)) {
			indexer::speed = -100;
		}

		// deploy macro
		if (master.get_digital(DIGITAL_A)) {
			intake::speed = 100;
			indexer::speed = 100;
			flywheel::speed = -70;
			intakes_open = true;
		}

		// chassis
		chassis::holonomic(master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		                   master.get_analog(ANALOG_LEFT_X) * (double)100 / 127,
		                   master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127);

		// update subsystems
		intake::move(intake::speed);
		indexer::move(indexer::speed);
		flywheel::move(flywheel::speed);
		ejector::move(ejector::speed);

		// update actuators
		if (intakes_open)
			intake::open();
		else
			intake::close();

		// ultrasonic debugging
		// std::array<double, 2> offsets = sensors::get_xy_offset(0);
		// printf("%.2lf,%.2lf\n", offsets[0], offsets[1]);

		delay(20);
	}
}
