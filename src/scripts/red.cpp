#include "ARMS/arc.h"
#include "ARMS/chassis.h"
#include "ARMS/odom.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/intake.hpp"

void red() {
	// deploy
	odom::reset({0, 0}, 180);
	intake::open();
	flywheel::move(-50);
	intake::move(100);
	indexer::move(60);
	ejector::move(100);
	delay(400);
	chassis::fast(-4);
	intake::close();

	// align with corner goal
	macro::intake();
	odom::holo({3, 15}, 127, 100, 150);

	// score 2 red, intake 2 blue               GOAL 1
	macro::cornerGoal(135, 2);
	macro::intake();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// backup
	chassis::fast(-4);
	macro::outtake();
	odom::holoThru({16, -12}, 180, 50, 100);

	// intake 1 red
	macro::intake();
	odom::holo({24, 0}, 88.4, 55, 100);

	// move to center red
	odom::holoThru({36, -10}, 0, 100, 150);

	// align and intake
	vision::alignFront(0);

	// align with side goal
	odom::holoAsync({60, -10}, 90, 100, 300);
	delay(700);
	chassis::waitUntilSettled();

	// move and score 2 red and intake 1 blue   GOAL 2
	chassis::tank(50, 50);
	delay(200);
	macro::doubleShot();
	macro::intake();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::move(-8);
	macro::outtake(60);
	chassis::turn(45);
	chassis::turn(-45);
	macro::intake();
	vision::alignBack(1, 300);

	// intake wall ball
	odom::holoAsync({34, 5}, 70, 80, 200);
	delay(700);
	chassis::waitUntilSettled();
	delay(100);

	// align and score corner goal                        GOAL 3
	odom::holo({52, -1}, 45, 100, 100);
	macro::cornerGoal(45, 2);
	intake::open();
	flywheel::move(80);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse and intake red
	ejector::move(100);
	chassis::arcLeft(-900, .4, 70);
	macro::intake();

	// intake second red
	odom::holoThru({-24, -28}, 90, 100, 100);
	vision::alignBack(3);

	// align with side goal and score           GOAL 4
	intake::close();
	odom::holoAsync({-7, -61}, 0, 100, 100);
	delay(1000);
	chassis::waitUntilSettled();
	chassis::tank(50, 50);
	delay(200);
	macro::doubleShot();
	macro::intake();

	// reset odom
	odom::reset({0, 0}, chassis::angle());
	intake::move(-100);
	chassis::fast(-8);

	// intake corner ball
	macro::eject();
	odom::holo({-8, -12}, -90, 100, 100);
	vision::alignFront(4, 100);
	macro::intake();

	// intake wall ball
	odom::holoAsync({-19, -60}, -90, 60, 100);
	delay(500);
	chassis::waitUntilSettled();
	delay(100);

	// align to goal and score                      GOAL 5
	macro::cornerGoal(-45, 2);
	flywheel::move(80);
	indexer::move(80);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	chassis::fast(-4);

	// intake center ball
	odom::holo({-32, 30}, 0, 100, 100);
	vision::alignBack(5, 350);
	macro::intake();

	// intake second ball and score             GOAL 6
	odom::holo({-62.5, 28}, -90, 100, 100);
	chassis::fast(28, 60);
	macro::score(1000);
	macro::intake();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse and move to intake
	chassis::fast(-12);
	macro::eject();
	odom::holoAsync({-40, 4}, -180, 70, 200);
	delay(500);
	odom::holoAsync({-31, 6}, -90, 70, 200);
	delay(500);
	macro::intake();
	chassis::waitUntilSettled();
	chassis::move(12);

	// align with goal and score                 GOAL 7
	odom::holo({-49, -1}, -135, 100, 100);
	macro::cornerGoal(-135, 1);
	flywheel::move(80);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse and intake red
	vision::alignBack(6, 500);
	macro::intake();

	// move to side goal and score               GOAL 8
	odom::holo({9, 59}, 180, 100, 100);
	chassis::tank(50, 50);
	delay(500);
	macro::score(450);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// intake red ball
	vision::alignBack(7);

	// align with center goal while shooting blue out of the top
	odom::holoAsync({36, 4}, 0, 30, 300);
	delay(250);
	macro::intake();
	chassis::waitUntilSettled();

	// move and intake two balls
	intake::open();
	macro::intake();
	ejector::move(-100);
	odom::holo({54, 3}, 0, 50, 300);
	intake::close(100);
	delay(800);

	// back up and score                         GOAL 9
	intake::open();
	delay(100);
	chassis::fast(-4);
	chassis::voltage(400);
	intake::close(100);
	macro::score(600);

	// reverse
	intake::open();
	chassis::fast(-12);
	//*/
}
