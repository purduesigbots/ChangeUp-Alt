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
	odom::holo({1, 21}, 127, 100, 150);

	// score 2 red, intake 2 blue               GOAL 1
	// macro::cornerGoal(135);

	// old score code
	// chassis::tank(40, 40);
	// delay(400);
	// macro::score(35, 500);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// backup and spit out blue
	chassis::fast(-4);
	intake::move(-100);
	odom::holoThru({16, -12}, 180, 50, 100);

	// intake 1 red
	macro::intake();
	odom::holo({24, 2}, 88.4, 55, 100);

	// move to center red
	odom::holoThru({41, -6}, 0, 100, 150);

	// align and intake
	macro::intake();
	vision::alignRedFront(1, 100);

	// align with side goal
	odom::holo({58, -6}, 90, 100, 300);

	// move and score 2 red and intake 1 blue   GOAL 2
	chassis::tank(50, 50);
	delay(600);
	macro::score(35, 400);
	flywheel::setEjectMode(true);
	macro::score(80, 350);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::fast(-4);
	intake::move(-100); // spit out any blue balls in the intake
	chassis::turnAsync(-180);
	delay(200);
	macro::eject();
	chassis::waitUntilSettled();

	// align and intake center red
	macro::intake();
	odom::holo({2, -44}, 270, 70, 100);

	// score middle goal                        GOAL 3
	macro::intake();
	indexer::move(80);
	ejector::move(-60);
	intake::open();
	chassis::moveAsync(6.5, 40);

	// intake bounce
	delay(400);
	intake::close();
	delay(400);
	intake::open();
	delay(150);
	intake::close();
	delay(400);
	intake::open();
	delay(150);
	intake::close();
	delay(400);

	// pull back to drop the blue
	intake::move(0);
	chassis::voltage(100, -100);
	delay(100);
	intake::move(100);
	chassis::voltage(50, 50);
	delay(300);

	// score the red ball
	macro::score(60, 400, 77);
	odom::reset({0, 0}, chassis::angle());
	delay(200);
	chassis::move(-24);

	// eject balls, move to ball, and intake
	macro::eject();
	odom::holo({22, 12}, 30);
	vision::alignRedFront();
	macro::intake();

	// intake wall ball
	odom::holo({29, 60}, 90);

	// align with corner goal
	odom::holo({54, 49}, 43, 100, 100);

	// move and score 2 red, intake 2 blue      GOAL 4
	chassis::tank(40, 40);
	delay(600);
	macro::score(35, 400);
	flywheel::setEjectMode(true);
	macro::score(80, 250);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse and intake wall ball
	chassis::fast(-6);
	intake::move(-100);

	// intake mid-field ball
	odom::holoThru({-34, -34}, -90, 100, 100);
	macro::eject();
	vision::alignRedFront(true, 80);
	macro::intake();

	// align with side goal
	odom::holo({-12, -61}, 0, 100, 100);

	// score 2 red and intake 1 blue            GOAL 5
	chassis::tank(60, 60);
	delay(800);
	macro::score(35, 400);
	flywheel::setEjectMode(true);
	macro::score(80, 250);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// outtake blue ball
	chassis::move(-12);

	// align with and intake corner ball
	macro::eject();
	odom::holoThru({-5, -16}, -70, 80, 100);
	vision::alignRedFront();
	macro::intake();

	// align with and intake wall ball
	macro::intake();
	odom::holo({-18, -66}, -90, 100, 100);

	// align with corner goal
	odom::holo({-2, -46}, -45, 100, 100);

	// score 2 red and intake 2 blue            GOAL 6
	chassis::tank(55, 55);
	delay(800);
	macro::score(35, 400);
	macro::score(70);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with red balls
	chassis::fast(-4);
	intake::move(-100);

	odom::holo({-41, 14}, 135, 100, 100);
	macro::eject();

	// intake with chained vision
	vision::alignRedFront(true, 0);
	macro::intake();
	chassis::voltage(600, 40, 65);
	vision::alignRedFront(false, 100);

	// align  with side goal and score          GOAL 7
	odom::holo({-110, 49}, 185, 100, 100);
	chassis::tank(60, 60);
	delay(600);
	macro::score(35, 400);
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
	chassis::tank(60, 60);
	delay(800);
	macro::score(35, 400);
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
	chassis::tank(40, 40);
	delay(400);
	macro::score(35, 400);
	macro::score(45);

	// back out
	chassis::fast(-12);
}
