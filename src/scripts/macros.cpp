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

void score() {
	indexer::move(100);
	flywheel::move(100);
}

void intake() {
	intake::move(100);
	indexer::move(50);
	flywheel::move(-10);
}

void outtake() {
	intake::move(-100);
	indexer::move(-100);
}

} // namespace macro
