#include "main.h"
#include "subsystems/flywheel.hpp"
#include "subsystems/indexer.hpp"
#include "subsystems/sensors.hpp"
namespace macro {

bool scoring = false;

void stopRollers() {
	indexer::move(0);
	flywheel::move(0);
}

void stopAll() {
	intake::move(0);
	stopRollers();
}

void score(double indexer_speed, int shootTime, int flywheel_speed) {
	scoring = true;
	indexer::move(indexer_speed);
	flywheel::setSpeed(flywheel_speed);
	flywheel::setState(1);
	delay(shootTime);

	int c = 0;

	while (c < shootTime && sensors::frontLineDetect()) {
		c += 10;
		delay(10);
	}
	indexer::move(60);
	scoring = false;
}

void intake(bool with_indexer) {
	intake::move(100);
	if (with_indexer) {
		indexer::move(60);
	}
}

void intakeBlue() {
	int c = 0;

	intake();
	flywheel::move(100);

	while (c < 1000 && sensors::backLineDetect()) {
		c += 10;
		delay(10);
	}
	/*
	  c = 0;

	  while (c < 1000 && sensors::frontLineDetect()) {
	    c += 10;
	    delay(10);
	  }
	*/
	flywheel::move(0);
}

void outtake(double max) {
	intake::move(-max);
	indexer::move(-100);
	flywheel::move(-100);
}

} // namespace macro
