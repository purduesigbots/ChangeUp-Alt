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
	sensor = std::make_shared<Vision>(10);

	vision_signature_s_t SIG_RED = Vision::signature_from_utility(
	    1, 2047, 8241, 5144, -655, 343, -156, 1.000, 0);
	sensor->set_signature(1, &SIG_RED);
	sensor->set_exposure(100);
}

bool detectBall() {
	int num = 6;

	vision_object_s_t object_arr[num];
	sensor->read_by_sig(0, 1, num, object_arr);

	for (int i = 0; i < num; i++) {
		if ((object_arr[i].x_middle_coord >= target - 60 &&
		     object_arr[i].x_middle_coord <= target + 60) &&
		    object_arr[i].y_middle_coord >= 170)
			return true;
	}

	return false;
}

bool checkBeforeRunning() {
	int num = 6;

	vision_object_s_t object_arr[num];
	if (sensor->read_by_sig(0, 1, num, object_arr) == 0)
		return false;
	else
		return true;
}

void alignRed(bool useActuation, int timeDelay,
              int base_speed) { // x 120 - 180 y 180 - 211

	for (int i = 0; i < 3; i++) {
		if (!checkBeforeRunning())
			return;
		delay(10);
	}

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

		if (x_pos == 0)
			speed = 0;

		chassis::tank(base_speed - speed, base_speed + speed);

		delay(10);
	}
	chassis::tank(base_speed, base_speed);

	if (useActuation) {
		intake::close();
	}

	delay(timeDelay);

	chassis::tank(0, 0);
}

} // namespace vision
