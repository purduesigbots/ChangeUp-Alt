#include "ARMS/chassis.h"
#include "main.h"
#include "subsystems/intake.hpp"

void blue() {
	// vision::alignRed();
	intake::close(100);
	delay(3000);
}
