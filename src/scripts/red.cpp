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
	odom::holoThru({14, 14}, 132, 80, 150);
	odom::holoThru({4, 24}, 132, 50, 150);

	// score 2 red, intake 2 blue               GOAL 1
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// move and outtake 2 blue
	odom::holo({12, -8}, 180, 100, 100);
	macro::outtake();
	delay(700);

	// align with wall red
	odom::holoThru({23, -10.4}, 88.4, 100, 100);

	// intake 1 red
	macro::intake(false);
	odom::holoThru({23, 2}, 88.4, 50, 100);

	// move to center red
	odom::holoThru({40.5, -4}, 0, 100, 100);

	// align and intake
	macro::intake();
	vision::alignRed();

	// align with side goal
	odom::holo({60, -14.8}, 90, 100, 300);

	// move and score 2 red and intake 1 blue   GOAL 2
	// vision::alignBlue();
	chassis::move(20);
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse, turn, and outtake 1 blue
	chassis::fast(-8, 60);
	delay(100);
	flywheel::move(-100);
	macro::outtake();
	chassis::turn(180);
	flywheel::move(0);

	// align and intake center red
	vision::alignRed();

	// align with middle goal and score         GOAL 3
	odom::holo({-3, -48}, 270, 100, 100);
	// vision::alignBlue();
	macro::intake();
	chassis::move(16);
	delay(400);
	macro::stopAll();
	chassis::move(-6);
	macro::intake();
	chassis::move(6);
	macro::score(50);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	intake::move(-100);
	chassis::move(-12, 80);

	// turn and eject 2 blue
	chassis::turn(-160);
	macro::outtake();
	delay(1000);
	macro::intake();

	// move to wall red and intake
	odom::holoThru({36, 40}, 90, 100, 100);
	odom::holoThru({36, 52}, 90, 50, 100);

	// align with corner goal
	odom::holo({57, 43}, 43.4, 100, 100);
	// vision::alignBlue();

	// move and score 2 red, intake 2 blue      GOAL 4
	chassis::move(24);
	macro::score(55);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// reverse
	intake::move(-100);
	chassis::fast(-8);

	// align with red ball and intake
	odom::holo({-36, -12}, 40, 100, 100);
	flywheel::move(-100);
	macro::outtake();
	delay(700);
	macro::stopAll();
	macro::intake();
	chassis::turn(-60);
	vision::alignRed();

	// align with red ball
	odom::holo({-10, -64}, -180, 100, 100);
	vision::alignRed();

	// align with side goal
	chassis::turn(180, 80);
	odom::holo({-12, -62}, 0, 100, 100);

	// score 2 red and intake 1 blue            GOAL 5
	chassis::move(25, 80);
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// outtake blue ball
	odom::holo({-8, 0}, 40, 100, 100);
	macro::outtake();
	delay(500);

	// align with and intake corner ball
	chassis::turn(-130);
	vision::alignRed();

	// align with wall ball
	odom::holo({-22, -55}, -90, 100, 100);

	// intake wall red
	macro::intake();
	chassis::move(10, 40);

	// align with corner goal
	odom::holo({-8, -48}, -45, 100, 100);

	// score 2 red and intake 2 blue            GOAL 6
	chassis::move(25);
	macro::score();

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with center red ball
	odom::holo({-36, 36}, -50, 100, 100);
	macro::outtake();
	delay(700);
	chassis::turn(-130);

	// intake center red ball
	macro::intake();
	vision::alignRed();

	// align  with side ball, intake and score  GOAL 7
	odom::holo({-60, 36}, -90, 100, 100);
	macro::intake();
	chassis::move(40, 80);
	macro::score(80);

	// reset odom
	odom::reset({0, 0}, chassis::angle());

	// align with wall ball
	odom::holo({-36, 8}, -90, 100, 100);
	/*
	  // intake wall ball
	  macro::intake();
	  chassis::move(20, 30);

	  // align with corner goal
	  odom::holo({-60, 8}, -130, 100, 100);

	  // score 1 red, intake 2 blue               GOAL 8
	  chassis::move(15);
	  macro::score();

	  // reset odom
	  odom::reset({0, 0}, chassis::angle());

	  // move out and outtake blue balls
	  odom::holo({36, 12}, -120, 100, 100);
	  macro::outtake();
	  delay(700);

	  // align with corner ball and intake
	  chassis::turn(-60);
	  macro::intake();
	  vision::alignRed();

	  // align with side goal
	  odom::holo({20, 60}, -180, 100, 100);

	  // score 1 red, intake 1 blue               GOAL 9
	  macro::intake();
	  chassis::move(15);
	  macro::score();

	  // reset odom
	  odom::reset({0, 0}, chassis::angle());

	  // reverse and outtake
	  chassis::move(-8);
	  /*
	    chassis::turn(-90);
	    macro::outtake();
	    delay(500);
	    macro::intake();

	    // align with ball and intake
	    chassis::turn(-90);
	    vision::alignRed();

	    // align with center goal
	    odom::holo({36, 0}, 0, 100, 100);

	    // intake 2 blue
	    macro::intake();
	    chassis::move(12);
	    macro::intakeBlue();

	    // back out to let 3rd blue drop
	    chassis::move(-6);

	    // score 1 red, intake 1 blue               GOAL 9
	    chassis::move(6);
	    macro::score();
	    chassis::move(-24);
	      */
}
