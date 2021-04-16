#include "ARMS/arc.h"
#include "ARMS/chassis.h"
#include "ARMS/odom.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/ejector.hpp"
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
	odom::holo({5, 15}, 127, 100, 150);

	// score 2 red, intake 2 blue               GOAL 1
	flywheel::setEjectMode(true);
	macro::cornerGoal(135, 2);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// backup and spit out blue
	chassis::fast(-4);
	macro::outtake(90);
	odom::holoThru({16, -12}, 180, 50, 100);
	flywheel::setEjectMode(false);

	// intake 1 red
	macro::intake();
	odom::holo({24, 0}, 88.4, 55, 100);

	// move to center red
	odom::holoThru({36, -10}, 180, 100, 150);

	// align and intake
	macro::intake();
	vision::alignRedBack();

	// align with side goal
	odom::holo({58, -10}, 90, 100, 300);

	// move and score 2 red and intake 1 blue   GOAL 2
	chassis::tank(50, 50);
	flywheel::setEjectMode(true);
	macro::score(40, 600);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::fast(-6);
	macro::outtake(60);
	chassis::turn(45);
	chassis::turn(-45);
	flywheel::setEjectMode(false);
	macro::intake();
	vision::alignRedBack();

	// align and intake center red
	odom::holoAsync({34, 5}, 70, 80, 200);
	delay(700);
	chassis::waitUntilSettled();
	delay(100);

	// align and score corner goal                        GOAL 3
	odom::holo({48, 0}, 45, 100, 100);
	macro::cornerGoal(45, 2);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse and intake red
	chassis::arcLeft(-500, 0.2);
	macro::intake();
	vision::alignRedBack();

	// intake second red
	odom::holoThru({-24, -28}, 90, 100, 100);
	vision::alignRedBack();

	// align with side goal and score           GOAL 4
	odom::holoAsync({-7, -60}, 0, 100, 100);
	delay(500);
	chassis::waitUntilSettled();
	chassis::tank(50, 50);
	flywheel::setEjectMode(true);
	macro::score(50, 700);

	// reset odom
	odom::reset({0, 0}, chassis::angle());
	chassis::fast(-8);

	// intake corner ball
	macro::eject();
	odom::holo({-8, -12}, -90, 100, 100);
	vision::alignRedFront(true, 100);
	macro::intake();
	flywheel::setEjectMode(false);

	// intake wall ball
	odom::holo({-19, -60}, -90, 60, 100);
	delay(100);

	// align to goal and score                      GOAL 5
	macro::cornerGoal(-45, 2);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	chassis::fast(-4);

	// intake center ball
	macro::intake();
	odom::holo({-32, 30}, 0, 100, 100);
	vision::alignRedBack(350);

	// intake second ball and score             GOAL 6
	odom::holo({-60, 28}, -90, 100, 100);
	macro::intake();
	chassis::fast(28, 60);
	flywheel::setEjectMode(true);
	macro::score(50, 600);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse and move to intake
	chassis::fast(-12);
	chassis::turn(-45);
	macro::eject();
	delay(200);
	odom::holoAsync({-40, 4}, -90, 70, 200);
	delay(800);
	chassis::waitUntilSettled();
	odom::holo({-40, -6}, -90, 50, 100);
	macro::intake();

	// align with goal and score                 GOAL 7
	odom::holo({-48, 0}, -135, 100, 100);
	macro::cornerGoal(-135, 1);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse and intake red
	chassis::arcLeft(-500, 0.2);
	macro::intake();
	vision::alignRedBack(500);

	// move to side goal and score               GOAL 8
	odom::holo({5, 61}, 180, 100, 100);
	chassis::tank(50, 50);
	delay(100);
	flywheel::setIndexerSpace(false);
	macro::score(50, 500);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// intake red ball
	macro::intake();
	vision::alignRedBack();

	// align with center goal
	odom::holo({36, 4}, 0, 30, 300);

	// move and intake two balls
	macro::intake();
	ejector::move(-100);
	chassis::move(22);
	delay(900);

	// back up and score                         GOAL 9
	intake::open();
	delay(100);
	chassis::fast(-4);
	chassis::voltage(400);
	intake::close(100);
	macro::score(10, 500, 85);

	// reverse
	intake::open();
	chassis::fast(-12);
}
