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
	indexer::move(60);
	scoring = false;
}

void intake(bool with_indexer) {
	intake::move(100);
	if (with_indexer) {
		indexer::move(60);
	}
}

void outtake(double max) {
	intake::move(-max);
	indexer::move(-100);
	flywheel::move(-100);
}

} // namespace macro
