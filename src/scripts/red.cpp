#include "ARMS/chassis.h"
#include "main.h"
#include "subsystems/flywheel.hpp"

void red() {

	// deploy
	flywheel::move(-50);
	intake::open();
	delay(400);
	flywheel::move(0);
	intake::close();
	macro::intake();
	flywheel::setState(2);

	// intake first ball
	indexer::move(100);
	odom::holoThru({12, 0}, 0, 100, 100);

	// align with corner goal
	odom::holo({10, 17}, 127, 100, 150);

	// score 2 red, intake 2 blue               GOAL 1
	chassis::fast(10, 40);
	macro::score(35, 350);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// backup and spit out blue
	chassis::fast(-4);
	intake::move(-100);
	odom::holoThru({17, -12}, 180, 50, 100);

	// intake 1 red
	macro::intake();
	odom::holoThru({25, -3}, 88.4, 40, 100);

	// move to center red
	odom::holoThru({44, -6}, 0, 100, 150);

	// align and intake
	macro::intake();
	vision::alignRed(1, 100);

	// align with side goal
	odom::holo({63, -6}, 90, 100, 300);

	// move and score 2 red and intake 1 blue   GOAL 2
	chassis::fast(5, 40);
	macro::score(80, 350);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::fast(-4);
	intake::move(-100); // spit out any blue balls in the intake
	chassis::turn(180);

	// align and intake center red
	vision::alignRed();

	// align with middle goal and score         GOAL 3
	odom::holo({-3, -44}, 270, 70, 100);
	intake::open(60);
	chassis::move(10);
	intake::close(100); // higher closing pressure to help descore
	chassis::tank(50, 50);
	delay(200);
	chassis::tank(0, 0);
	macro::score(80, 400, 77);
	flywheel::setState(0);
	flywheel::move(0);
	macro::intake();
	odom::reset({0, 0}, chassis::angle());

	// reverse
	intake::close();
	chassis::fast(-4, 100);

	// turn and eject 2 blue
	flywheel::setState(2);
	flywheel::setSpeed(100);

	chassis::fast(-4, 100);

	// move to wall red and intake
	macro::intake();
	odom::holoThru({20, 30}, 180, 100, 150);
	odom::holoThru({33, 39}, 90, 100, 150);
	odom::holoThru({36, 49}, 90, 50, 150);

	// move to corner red and intake
	odom::holoThru({36, 40}, -45, 100, 320);
	vision::alignRed(true, 100);

	// align with corner goal
	odom::holoAsync({56, 45}, 43.4, 100, 100);
	delay(1000);
	chassis::waitUntilSettled();

	// move and score 2 red, intake 2 blue      GOAL 4
	chassis::fast(13, 40);
	macro::score(100);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	chassis::fast(-6);
	intake::move(-100);
	chassis::fast(-10, 30);

	// align with red ball
	odom::holoThru({-34, -34}, -90, 100, 100);
	macro::intake();
	vision::alignRed(true, 80);

	// align with side goal
	odom::holo({-12, -61}, 0, 100, 100);

	// score 2 red and intake 1 blue            GOAL 5
	chassis::fast(8, 40);
	macro::score(80, 250);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// outtake blue ball
	chassis::fast(-4);
	intake::move(-100);
	chassis::move(-4);
	delay(250); // time to get rid of blue

	// align with and intake corner ball
	odom::holoThru({-7, -16}, -70, 80, 100);
	macro::intake();
	vision::alignRed();

	// align with and intake wall ball
	macro::intake();
	odom::holo({-20, -66}, -90, 100, 100);

	// align with corner goal
	odom::holo({-4, -48}, -45, 100, 100);

	// score 2 red and intake 2 blue            GOAL 6
	chassis::fast(15, 40);
	macro::score(70);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with red balls
	chassis::fast(-4);
	intake::move(-100);
	odom::holoAsync({-41, 14}, chassis::angle(), 100, 100);
	delay(400);
	odom::holo({-41, 14}, 135, 100, 100);
	macro::intake();

	// intake with chained vision
	vision::alignRed(true, 500);
	vision::alignRed(true, 100);

	// align  with side goal and score          GOAL 7
	odom::holo({-110, 66}, 180, 100, 100);
	chassis::fast(10, 40);
	macro::score(70);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, intake corner red
	chassis::fast(-4);
	intake::move(-100);
	chassis::move(-4);
	delay(250); // time to get rid of blue

	odom::holoThru({12, -10}, 270, 100, 100);
	macro::intake();
	vision::alignRed();

	// align with corner goal
	odom::holo({9, -52.5}, 223, 100, 100);

	// score                                    GOAL 8
	chassis::fast(13, 40);
	macro::score(65, 400, 75);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, intake red ball
	chassis::fast(-6);
	intake::move(-100);
	chassis::fast(-4);
	odom::holo({22, 8}, 180, 100, 100);
	macro::intake();
	odom::holoThru({22, -8}, 270, 40, 150);

	// move to line ball
	odom::holoThru({32, 8}, 360, 100, 100);

	// intake `line` ball
	vision::alignRed();

	// align with side goal
	odom::holo({62, 8}, 270, 100, 100);

	// move and score                           GOAL 9
	chassis::fast(9, 40);
	macro::score(45);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// move to center goal                      POKE
	chassis::fast(-4);
	odom::holoThru({-1, 46}, 93, 100, 300);
	chassis::voltage(200);

	// reverse
	chassis::fast(-24);
}
