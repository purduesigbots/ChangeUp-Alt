#include "main.h"
#include "subsystems/indexer.hpp"

void red() {
	// deploy
  intake::move(100);
	indexer::move(100);
	flywheel::move(-100);
	delay(500);
	indexer::move(100);
	flywheel::move(-10);
	chassis::move(12);
	odom::holo({14, 14}, 132);
	indexer::move(50);
	chassis::move(10);

	delay(50);
	chassis::fast(6, 40);
	chassis::voltage(10);
	delay(300);
	intake::move(100);
	indexer::move(100);
	macro::score();
	delay(1500);
	intake::move(0);
	delay(600);
	/*
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
	  */
}
