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

	// intake first ball
	indexer::move(100);
	flywheel::move(-10);
	chassis::move(12);

	// align with corner goal
	odom::holo({14, 14}, 132);
	indexer::move(50);
	chassis::move(14);

	// score 2 red, intake 2 blue
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// move and outtake 2 blue
	odom::holo({12, -8}, 180);
	macro::outtake();
	delay(700);

	// align with wall red
	odom::holo({23, -10.4}, 88.4);

	// intake 1 red
	macro::intake();
	chassis::move(15, 30);

	// move to center red
	odom::holo({40.5, -12}, 0);

	// align and intake
	vision::align();

	// align with side goal
	odom::holo({62, -14.8}, 88.6);

	// move and score 2 red and intake 1 blue
	chassis::move(18);
	macro::score(60);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::fast(-8);
	delay(100);
	flywheel::move(-100);
	macro::outtake();
	chassis::turn(180);
	flywheel::move(0);

	// align and intake center red
	vision::align();

	// move to wall red and intake
	odom::holo({36.1, -2.2}, 87.5);
	macro::intake();
	chassis::move(8, 40);

	// align with corner goal
	odom::holo({55.3, -3.9}, 43.4);

	// move and score 2 red, intake 2 blue
	chassis::move(14);
	macro::score(60);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	intake::move(-100);
	chassis::fast(-10);

	// align with red ball and intake
	odom::holo({-36, -12}, 30);
	flywheel::move(-100);
	macro::outtake();
	delay(700);
	macro::stopAll();
	macro::intake();
	chassis::turn(-60);
	vision::align();

	// align with red ball
	odom::holo({-12, -64}, -180);
	vision::align();

	// align with side goal
	chassis::turn(180, 80);
	odom::holo({-12, -62}, 0);

	// score 2 red and intake 1 blue
	chassis::move(25, 40);
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// outtake blue ball
	odom::holo({-8, 0}, 30);
	macro::outtake();
	delay(500);

	// align with and intake corner ball
	chassis::turn(-120);
	vision::align();

	// align with wall ball
	odom::holo({-22, -55}, -90);

	// intake wall red
	macro::intake();
	chassis::move(15, 30);

	// align with corner goal
	odom::holo({-8, -48}, -45);

	// score 2 red and intake 2 blue
	chassis::move(17);
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with center red ball
	odom::holo({-36, 36}, -50);
	macro::outtake();
	delay(700);
	chassis::turn(-130);

	// intake center red ball
	macro::intake();
	vision::align();

	// align  with side ball, intake and score
	odom::holo({-60, 36}, -90);
	macro::intake();
	chassis::move(40, 80);
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with wall ball
	odom::holo({-36, 8}, -90);

	// intake wall ball
	macro::intake();
	chassis::move(15, 30);

	// align with corner goal
	odom::holo({-60, 8}, -130);

	// score 2 red, intake 2 blue
	chassis::move(15);
	macro::score();
}
