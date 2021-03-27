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
	flywheel::setSpeed(flywheel_speed);
	flywheel::setState(1);
	delay(50);
	indexer::move(indexer_speed);
	delay(shootTime);
	indexer::move(50);
	scoring = false;
}

void intake() {
	flywheel::setState(2);
	flywheel::setSpeed(70);
	intake::move(100);
	indexer::move(60);
	ejector::move(100);
}

void eject() {
	flywheel::move(-100);
	indexer::move(-100);
	ejector::move(-100);
}

void outtake(double max) {
	intake::move(-max);
	indexer::move(-100);
	flywheel::move(-100);
}

} // namespace macro
