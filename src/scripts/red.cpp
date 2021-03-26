#include "macros.hpp"
#include "main.h"
#include "subsystems/flywheel.hpp"
#include "subsystems/intake.hpp"

void red() {

	// deploy
	odom::reset({0, 0}, 180);
	flywheel::move(-50);
	intake::open();
	macro::intake();
	chassis::fast(-4);
	flywheel::move(0);
	intake::close();
	flywheel::setState(2);

	// align with corner goal
	odom::holo({0, 19}, 127, 100, 150);

	// score 2 red, intake 2 blue               GOAL 1
	chassis::tank(40, 40);
	delay(400);
	macro::score(35, 400);

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
	vision::alignRedFront(1, 100);

	// align with side goal
	odom::holo({59, -6}, 90, 100, 300);

	// move and score 2 red and intake 1 blue   GOAL 2
	chassis::voltage(500, 40);
	flywheel::setEjectMode(true);
	macro::score(80, 350);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::fast(-4);
	intake::move(-100); // spit out any blue balls in the intake
	chassis::turn(180);
	macro::eject();

	// align and intake center red
	vision::alignRedFront();
	macro::intake();

	// align with middle goal and score         GOAL 3
	odom::holo({0, -44}, 270, 70, 100);
	macro::intake();
	ejector::move(-50);
	chassis::move(12);
	delay(500);
	indexer::move(60);
	intake::move(100);
	delay(1000);
	chassis::voltage(100, -100);
	delay(80);
	chassis::voltage(200, 50);
	delay(500);
	macro::score(60, 400, 77);
	odom::reset({0, 0}, -90);
	delay(200);
	chassis::move(-24);

	// eject balls, move to ball, and intake
	macro::eject();
	odom::holo({20, 12}, 30);
	vision::alignRedFront();
	macro::intake();

	// align with corner goal
	odom::holoAsync({52, 50}, 43.4, 100, 100);

	// move and score 2 red, intake 2 blue      GOAL 4
	chassis::voltage(500, 60);
	macro::score(100);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	macro::intake();
	odom::holoThru({-12, 0}, 90);
	vision::alignRedBack();
	odom::holoThru({-36, -36}, 90);
	vision::alignRedBack();

	// align with side goal
	odom::holo({-12, -61}, 0, 100, 100);

	// score 2 red and intake 1 blue            GOAL 5
	chassis::voltage(500, 40);
	flywheel::setEjectMode(true);
	macro::score(80, 250);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// outtake blue ball
	chassis::fast(-6);
	intake::move(-100);

	// align with and intake corner ball
	macro::eject();
	odom::holoThru({-7, -16}, -70, 80, 100);
	vision::alignRedFront();
	macro::intake();

	// align with and intake wall ball
	macro::intake();
	odom::holo({-20, -66}, -90, 100, 100);

	// align with corner goal
	odom::holo({-4, -48}, -45, 100, 100);

	// score 2 red and intake 2 blue            GOAL 6
	chassis::voltage(500, 40);
	macro::score(70);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with red balls
	chassis::fast(-4);
	intake::move(-100);

	odom::holo({-41, 14}, 135, 100, 100);
	macro::eject();

	// intake with chained vision
	vision::alignRedFront(true, 500);
	macro::intake();
	vision::alignRedFront(true, 100);

	// align  with side goal and score          GOAL 7
	odom::holo({-110, 66}, 180, 100, 100);
	chassis::voltage(500, 40);
	macro::score(70);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, intake corner red
	chassis::fast(-4);
	intake::move(-100);
	chassis::move(-4);

	odom::holoThru({12, -10}, 270, 100, 100);
	macro::eject();
	vision::alignRedFront();
	macro::intake();

	// align with corner goal
	odom::holo({9, -52.5}, 223, 100, 100);

	// score                                    GOAL 8
	chassis::voltage(500, 40);
	macro::score(65, 400, 75);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, intake red ball
	chassis::fast(-6);
	intake::move(-100);
	chassis::fast(-4);
	odom::holo({22, 8}, 180, 100, 100);
	macro::eject();
	odom::holoThru({22, -8}, 270, 40, 150);
	macro::intake();

	// move to line ball
	odom::holoThru({32, 8}, 360, 100, 100);

	// intake `line` ball
	vision::alignRedFront();

	// align with side goal
	odom::holo({62, 8}, 270, 100, 100);

	// move and score                           GOAL 9
	chassis::voltage(500, 40);
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
