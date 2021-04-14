#include "ARMS/chassis.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/ejector.hpp"
#include "subsystems/indexer.hpp"
#include "subsystems/vision.hpp"

void blue() {
	odom::reset({0, 0}, 90);
}
