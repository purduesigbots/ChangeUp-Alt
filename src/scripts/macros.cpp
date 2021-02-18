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
	delay(1000);
	macro::intakeBlue();
}

void intake(bool with_indexer) {
	intake::move(100);
	if (with_indexer) {
		indexer::move(100);
	}
	flywheel::move(0);
}

void intakeBlue() {
	intake();
	flywheel::move(100);

	while (sensors::backLineDetect()) {
		delay(10);
	}

	while (sensors::frontLineDetect()) {
		delay(10);
	}

	flywheel::move(0);
}

void outtake() {
	intake::move(-100);
	indexer::move(-100);
	flywheel::move(-100);
}

} // namespace macro
