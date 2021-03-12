#include "ARMS/chassis.h"
#include "ARMS/odom.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/indexer.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/vision.hpp"

void red() {

	// deploy
	flywheel::move(-50);
	intake::open();
	delay(300);
	flywheel::move(0);
	intake::close();
	macro::intake();

	// intake first ball
	indexer::move(100);
	odom::holoThru({12, 0}, 0, 100, 100);

	// align with corner goal
	odom::holo({10, 17}, 127, 100, 150);

	// score 2 red, intake 2 blue               GOAL 1
	chassis::fast(8, 50);
	macro::score(40);
	chassis::move(13, 50);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// backup and spit out blue
	chassis::fast(-4);
	odom::holoThru({17, -12}, 180, 50, 100);

	// intake 1 red
	macro::intake();
	odom::holoThru({25, 0}, 88.4, 40, 100);

	// move to center red
	odom::holoThru({38, -4}, 0, 100, 150);

	// align and intake
	macro::intake();
	vision::alignRed(1, 100);

	// align with side goal
	odom::holo({66, -14.8}, 90, 100, 300);

	// move and score 2 red and intake 1 blue   GOAL 2
	chassis::fast(8, 60);
	macro::score(45);
	chassis::move(14, 60);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::fast(-4);
	intake::move(-100); // spit out any blue balls in the intake
	chassis::fast(-4);
	chassis::turnAbsolute(270, 80);

	// align and intake center red
	vision::alignRed();

	// align with middle goal and score         GOAL 3
	odom::holo({-2, -44}, 270, 70, 100);
	macro::intake();
	chassis::move(16);
	intake::close(100); // higher closing pressure to help descore
	/*chassis::move(-6); //removing the jiggle for time saving
	intake::close();
	chassis::move(6);*/
	delay(500);
	macro::score(50, 100, 70);
	odom::reset({0, 0}, chassis::angle());

	// reverse
	intake::open();
	chassis::move(-12, 100);
	intake::close();

	// turn and eject 2 blue
	macro::outtake(70);

	// move to wall red and intake
	odom::holo({39, 40}, 180, 100, 100);
	macro::intake();
	odom::holoThru({38, 48}, 90, 50, 100);

	// move to corner red and intake
	odom::holoThru({34, 42}, -20, 100, 300);
	vision::alignRed(1, 70);

	// align with corner goal
	odom::holo({57, 43}, 43.4, 100, 100);

	// move and score 2 red, intake 2 blue      GOAL 4
	chassis::fast(16);
	macro::score(70);
	chassis::move(14);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	chassis::fast(-12, 30);

	// align with red ball
	odom::holoThru({-34, -34}, -90, 100, 100);
	macro::intake();
	vision::alignRed();

	// align with side goal
	odom::holo({-12, -61}, 0, 100, 100);

	// score 2 red and intake 1 blue            GOAL 5
	chassis::fast(10, 60);
	macro::score(45, 100);
	chassis::move(15, 60);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// outtake blue ball
	odom::holo({-10, 0}, 40, 100, 150);
	delay(200);

	// align with and intake corner ball
	odom::holoThru({-8, -16}, -90, 80, 100);
	macro::intake();
	vision::alignRed();

	// align with wall ball
	odom::holo({-20, -57}, -90, 100, 100);

	// intake wall red
	macro::intake();
	chassis::move(10, 50);

	// align with corner goal
	odom::holo({-8, -48}, -45, 100, 100);

	// score 2 red and intake 2 blue            GOAL 6
	chassis::fast(13);
	macro::score();
	chassis::move(14);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with red balls
	chassis::fast(-12);
	macro::outtake();
	odom::holo({-36, 12}, 135, 100, 100);
	macro::intake();

	// intake with chained vision
	vision::alignRed(true, 400);
	delay(100);
	vision::alignRed(false);

	// align  with side goal and score          GOAL 7
	odom::holo({-106, 64}, 180, 100, 100);
	chassis::fast(13, 80);
	macro::score(65);
	chassis::move(12, 80);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, intake corner red
	chassis::fast(-8);
	odom::holoThru({12, -10}, 90, 100, 100);
	chassis::turnAbsolute(270);
	macro::intake();
	vision::alignRed();

	// align with corner goal
	odom::holo({11, -50}, 223, 100, 100);

	// score                                    GOAL 8
	chassis::fast(10);
	macro::score(65, 100);
	chassis::move(10);

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
	chassis::fast(10);
	macro::score();
	chassis::move(10);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// move to center goal
	chassis::fast(-6);
	odom::holo({-3, 56}, 90, 100, 200);

	// reverse
	chassis::fast(-24);
}
