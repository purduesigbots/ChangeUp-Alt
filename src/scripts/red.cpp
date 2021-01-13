#include "main.h"

void red() {
	// deploy
	indexer::move(100);
	chassis::move(6);
	indexer::move(0);

	// goal 1
	macro::intake();
	odom::holoThru({34, 0}, 0);
	odom::holo({60, 12}, -35);
	odom::holo({32, 19}, -80); // align
	chassis::fast(6, 50);
	chassis::voltage(10);
	macro::score();
	delay(1500);
	intake::move(0);
	delay(600);
}
