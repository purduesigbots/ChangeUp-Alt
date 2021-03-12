#include "pros/vision.h"
#include "ARMS/chassis.h"
#include "main.h"
#include "sensors.hpp"

const int target = 160;
const double kp_red = .4;
const double kd_red = .8;
const double kp_blue = .6;
const double kd_blue = .8;
const int minimum = 300;

namespace vision {

std::shared_ptr<Vision> sensor;

void init() {
	sensor = std::make_shared<Vision>(18);

	vision_signature_s_t SIG_RED = Vision::signature_from_utility(
	    1, 5461, 7963, 6712, -1301, -337, -819, 2.700, 1);
	vision_signature_s_t SIG_BLUE = Vision::signature_from_utility(
	    2, -2941, -845, -1893, 4095, 7183, 5639, 2.800, 0);

	sensor->set_signature(1, &SIG_RED);
	sensor->set_signature(2, &SIG_BLUE);
}

bool detectBall() {
	int num = 6;

	vision_object_s_t object_arr[num];
	sensor->read_by_sig(0, 1, num, object_arr);

	for (int i = 0; i < num; i++) {
		if ((object_arr[i].x_middle_coord >= target - 60 &&
		     object_arr[i].x_middle_coord <= target + 60) &&
		    object_arr[i].y_middle_coord >= 180)
			return true;
	}

	return false;
}

void alignRed(bool useActuation, int timeDelay,
              int base_speed) { // x 120 - 180 y 180 - 211

	int pe = 0;

	if (useActuation) {
		intake::open();
	}
	intake::move(100);

	while (!detectBall()) {
		int x_pos =
		    sensor->get_by_sig(0, 1).x_middle_coord; // 0 = largest object, 1 = id
		int error = target - x_pos;
		int derivative = error - pe;
		int speed = error * kp_red + derivative * kd_red;
		pe = error;

		chassis::tank(base_speed - speed, base_speed + speed);

		delay(10);
	}

	delay(timeDelay);

	if (useActuation) {
		intake::close();
	}
	chassis::tank(0, 0);
}

void alignBlue() {

	int pe = 0;
	int count = 0;

	while (true) {
		int x_pos =
		    sensor->get_by_sig(0, 2).x_middle_coord; // 0 = largest object, 1 = id
		int error = target - x_pos;
		int derivative = error - pe;
		int speed = error * kp_blue + derivative * kd_blue;
		pe = error;

		chassis::holonomic(0, 0, -speed);

		if (count < minimum) {
			count += 10;
		} else if (chassis::settled()) {
			break;
		}

		delay(10);
	}
}

} // namespace vision
