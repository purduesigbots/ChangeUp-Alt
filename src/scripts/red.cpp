#include "ARMS/chassis.h"
#include "ARMS/odom.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/indexer.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/vision.hpp"

void red() {

	// deploy
	intake::move(100);
	indexer::move(100);
	flywheel::move(-100);
	delay(500);
	flywheel::move(0);

	// intake first ball
	indexer::move(100);
	odom::holoThru({12, 0}, 0, 100, 100);

	// align with corner goal
	odom::holo({9, 17}, 129, 100, 150);
	chassis::move(20, 50);

	// score 2 red, intake 2 blue               GOAL 1
	macro::score(65);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with wall red
	chassis::fast(-12);
	odom::holo({22, -7.4}, 180, 50, 100);

	// intake 1 red
	macro::intake();
	odom::holoThru({22, 2}, 88.4, 40, 100);

	// move to center red
	odom::holoThru({34.5, -4}, 0, 100, 100);

	// align and intake
	macro::intake();
	vision::alignRed();

	// align with side goal
	odom::holo({60, -14.8}, 90, 100, 300);

	// move and score 2 red and intake 1 blue   GOAL 2
	chassis::move(25);
	macro::score(65);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	odom::holo({0, -6}, 140, 100, 90);
	chassis::turn(140);
	flywheel::move(0);

	// align and intake center red
	vision::alignRed();

	// align with middle goal and score         GOAL 3
	odom::holo({-4, -44}, 270, 70, 100);
	macro::intake();
	chassis::move(17);
	delay(400);
	intake::open();
	chassis::move(-6);
	intake::close();
	chassis::move(6);
	odom::reset({0, 0}, chassis::angle());
	macro::score(50);
	flywheel::move(0);

	// reverse
	intake::open();
	chassis::move(-12, 100);
	intake::close();

	// turn and eject 2 blue
	chassis::turn(-100);
	macro::outtake();

	// move to wall red and intake
	odom::holo({36, 40}, 180, 100, 100);
	macro::intake();
	odom::holoThru({36, 45}, 90, 50, 100);

	// move to corner red and intake
	odom::holoThru({36, 40}, -20, 100, 300);
	vision::alignRed();

	// align with corner goal
	odom::holo({57, 43}, 43.4, 100, 100);

	// move and score 2 red, intake 2 blue      GOAL 4
	chassis::move(34);
	macro::score(60);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	chassis::fast(-12, 30);

	// align with red ball
	odom::holoThru({-36, -34}, -90, 100, 100);
	macro::intake();
	vision::alignRed();

	// align with side goal
	odom::holo({-12, -61}, 0, 100, 100);

	// score 2 red and intake 1 blue            GOAL 5
	chassis::move(30, 60);
	macro::score(50);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// outtake blue ball
	odom::holo({-8, 0}, 40, 100, 150);
	delay(200);

	// align with and intake corner ball
	odom::holoThru({-8, -16}, -90, 80, 100);
	macro::intake();
	vision::alignRed();

	// align with wall ball
	odom::holo({-20, -57}, -90, 100, 100);

	// intake wall red
	macro::intake();
	chassis::move(16, 40);

	// align with corner goal
	odom::holo({-10, -50}, -45, 100, 100);

	// score 2 red and intake 2 blue            GOAL 6
	chassis::move(34);
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with red balls
	chassis::fast(-12);
	macro::outtake();
	odom::holo({-36, 12}, 135, 100, 100);
	macro::intake();

	// intake with chained vision
	vision::alignRed();
	delay(100);
	vision::alignRed(false);

	// align  with side goal and score          GOAL 7
	odom::holo({-106, 63}, 180, 100, 100);
	chassis::move(34, 80);
	macro::score(65);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, intake corner red
	chassis::fast(-8);
	odom::holoThru({12, -16}, 270, 100, 100);
	macro::intake();
	vision::alignRed();

	// align with corner goal
	odom::holo({11, -54}, 225, 100, 100);

	// score                                    GOAL 8
	chassis::move(25);
	macro::score(65);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, intake red ball
	chassis::fast(-12);
	odom::holo({22, 12}, 180, 100, 100);
	macro::intake();
	odom::holoThru({22, -2}, 270, 40, 150);

	// move to line ball
	odom::holoThru({32, 12}, 360, 100, 100);

	// intake line ball
	vision::alignRed();

	// align with side goal
	odom::holo({60, 12}, 270, 100, 100);

	// move and score                            GOAL 9
	chassis::move(25);
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// move to center goal
	chassis::fast(-6);
	odom::holo({-4, 56}, 90, 100, 200);

	// reverse
	chassis::fast(-24);
}
