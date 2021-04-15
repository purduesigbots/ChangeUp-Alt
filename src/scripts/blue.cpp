#include "ARMS/arc.h"
#include "ARMS/chassis.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/ejector.hpp"
#include "subsystems/indexer.hpp"
#include "subsystems/vision.hpp"

void blue() {
	chassis::arcLeft(2000, 0.3, 100);
	delay(1000);
	chassis::waitUntilSettled();
}
