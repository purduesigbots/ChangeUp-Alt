#include "ARMS/chassis.h"
#include "ARMS/odom.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/flywheel.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/vision.hpp"

void red() {
	// deploy
	odom::reset({0, 0}, 180);
	flywheel::move(-50);
	intake::open();
	macro::intake();
	delay(500);
	chassis::fast(-4);
	flywheel::move(0);
	intake::close();
	flywheel::setState(2);

	// align with corner goal
	odom::holo({1, 21}, 127, 100, 150);

	// score 2 red, intake 2 blue               GOAL 1
	macro::cornerGoal(135, 2);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// backup and spit out blue
	chassis::fast(-4);
	intake::move(-100);
	odom::holoThru({16, -12}, 180, 50, 100);

	// intake 1 red
	macro::intake();
	odom::holo({24, 4}, 88.4, 55, 100);

	// move to center red
	odom::holoThru({36, -10}, 180, 100, 150);

	// align and intake
	macro::intake();
	vision::alignRedBack();

	// align with side goal
	odom::holo({52, -10}, 90, 100, 300);
	macro::sideGoal(90);

	// move and score 2 red and intake 1 blue   GOAL 2
	chassis::tank(50, 50);
	macro::score(40, 400);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::fast(-8);
	macro::intake();
	vision::alignRedBack();

	// align and intake center red
	odom::holoThru({36, 0}, 90, 70, 100);
	odom::holo({36, 8}, 90, 60);

	// align and score corner goal                        GOAL 3
	odom::holo({48, 0}, 45, 100, 100);
	macro::cornerGoal(45, 2);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse and intake red
	chassis::fast(-4);
	odom::holoThru({-12, -12}, 90, 60, 100);
	macro::intake();
	vision::alignRedBack();

	// intake second red
	odom::holoThru({-36, -36}, 90, 100, 100);
	vision::alignRedBack();
}
