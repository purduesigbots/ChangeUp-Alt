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

	// intake first ball
	indexer::move(100);
	odom::holoThru({12, 0}, 0, 100, 100);

	// align with corner goal
	odom::holo({10, 17}, 127, 100, 150);

	// score 2 red, intake 2 blue               GOAL 1
	chassis::fast(10, 50);
	macro::score(40, 350);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// backup and spit out blue
	chassis::fast(-4);
	odom::holoThru({17, -12}, 180, 50, 100);

	// intake 1 red
	macro::intake();
	odom::holoThru({25, 0}, 88.4, 40, 100);

	// move to center red
	odom::holoThru({46, -4}, 0, 100, 150);

	// align and intake
	macro::intake();
	vision::alignRed(1, 100);

	// align with side goal
	odom::holo({66, -6}, 90, 100, 300);

	// move and score 2 red and intake 1 blue   GOAL 2
	chassis::fast(7, 50);
	macro::score(35, 350);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::fast(-4);
	intake::move(-100); // spit out any blue balls in the intake
	chassis::fast(-4);
	chassis::tank(80, -80);
	delay(100);
	chassis::turnAbsolute(270, 80);

	// align and intake center red
	vision::alignRed();

	// align with middle goal and score         GOAL 3
	odom::holo({-2, -44}, 270, 70, 100);
	chassis::move(14);
	intake::close(100); // higher closing pressure to help descore
	macro::score(50, 200, 90);
	flywheel::setState(0);
	macro::intake();
	odom::reset({0, 0}, chassis::angle());

	// reverse
	intake::close();
	chassis::move(-12, 100);

	// turn and eject 2 blue
	flywheel::setState(2);
	flywheel::setSpeed(60);
	chassis::tank(-80, 80);
	delay(80);

	// move to wall red and intake
	odom::holo({39, 40}, 90, 100, 100);
	macro::intake();
	odom::holoThru({38, 48}, 90, 50, 100);

	// move to corner red and intake
	odom::holoThru({37, 39}, -20, 100, 300);
	vision::alignRed(1, 70);

	// align with corner goal
	odom::holo({56, 44}, 43.4, 100, 100);

	// move and score 2 red, intake 2 blue      GOAL 4
	chassis::fast(16, 50);
	macro::score(70);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	chassis::fast(-12, 30);

	// align with red ball
	odom::holoThru({-34, -34}, -90, 100, 100);
	macro::intake();
	vision::alignRed(true, 80);

	// align with side goal
	odom::holo({-12, -61}, 0, 100, 100);

	// score 2 red and intake 1 blue            GOAL 5
	chassis::fast(13, 50);
	macro::score(45, 100);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// outtake blue ball
	odom::holo({-10, 0}, 40, 50, 150);

	// align with and intake corner ball
	odom::holoThru({-8, -16}, -90, 80, 100);
	macro::intake();
	vision::alignRed();

	// align with and intake wall ball
	macro::intake();
	odom::holo({-20, -69}, -90, 100, 100);

	// align with corner goal
	odom::holo({-4, -50}, -45, 100, 100);

	// score 2 red and intake 2 blue            GOAL 6
	chassis::fast(15, 60);
	macro::score(35);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with red balls
	chassis::fast(-12);
	odom::holo({-40, 16}, 135, 100, 100);
	macro::intake();

	// intake with chained vision
	vision::alignRed(true, 600);
	vision::alignRed();

	// align  with side goal and score          GOAL 7
	odom::holo({-110, 62}, 180, 100, 100);
	chassis::fast(15, 50);
	macro::score(65);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, intake corner red
	chassis::fast(-8);
	odom::holoThru({12, -10}, 270, 100, 100);
	macro::intake();
	vision::alignRed();

	// align with corner goal
	odom::holo({9, -49}, 223, 100, 100);

	// score                                    GOAL 8
	chassis::fast(13, 50);
	macro::score(65);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, intake red ball
	chassis::fast(-12);
	odom::holo({22, 7}, 180, 100, 100);
	macro::intake();
	odom::holoThru({22, -9}, 270, 40, 150);

	// move to line ball
	odom::holoThru({32, 7}, 360, 100, 100);

	// intake `line` ball
	vision::alignRed();

	// align with side goal
	odom::holo({60, 8}, 270, 100, 100);

	// move and score                           GOAL 9
	chassis::fast(10, 50);
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// move to center goal                      POKE
	chassis::fast(-6);
	odom::holo({-2, 54}, 90, 100, 200);

	// reverse
	chassis::fast(-24);
}
