#include "ARMS/chassis.h"
#include "macros.hpp"
#include "main.h"
#include "subsystems/ejector.hpp"
#include "subsystems/indexer.hpp"
#include "subsystems/vision.hpp"

void blue() {
	macro::sideGoalAlign(0);
}
