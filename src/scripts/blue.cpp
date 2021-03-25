#include "main.h"
#include "subsystems/indexer.hpp"
#include "subsystems/vision.hpp"

void blue() {
	odom::reset({0, 0}, 45);
	macro::intake();
	odom::holoThru({-12, -12}, 90);
	vision::alignRedBack();
	odom::holoThru({-36, -48}, 90);
	vision::alignRedBack();
}
