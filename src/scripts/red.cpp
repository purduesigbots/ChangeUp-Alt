#include "main.h"
#include "subsystems/indexer.hpp"

void red() {
	// deploy
  intake::move(100);
	indexer::move(100);
	flywheel::move(-100);
	delay(500);
	indexer::move(0);
	flywheel::move(0);
	chassis::move(12);
	chassis::turn(120);
	odom::holoThru({22.6, 11.6}, 120);
	// delay(50);
	// chassis::fast(6, 40);
	// chassis::voltage(10);
	// delay(300);
	// intake::move(100);
	// indexer::move(100);
	// macro::score();
	// delay(1500);
	// intake::move(0);
	// delay(600);
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
