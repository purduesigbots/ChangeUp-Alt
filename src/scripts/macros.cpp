#include "main.h"
namespace macro {

void stopRollers() {
	indexer::move(0);
	flywheel::move(0);
}

void stopAll() {
	intake::move(0);
	stopRollers();
}

void score(double indexer_speed) {
	indexer::move(indexer_speed);
	flywheel::move(100);
	delay(950);
	macro::intakeBlue();
}

void intake() {
	intake::move(100);
	indexer::move(80);
	flywheel::move(-10);
}

void intakeBlue() {
	intake();

	while (sensors::backLineDetect()) {
		delay(10);
	}

	while (sensors::frontLineDetect()) {
		delay(10);
	}
}

void outtake() {
	intake::move(-80);
	indexer::move(-100);
}

} // namespace macro
