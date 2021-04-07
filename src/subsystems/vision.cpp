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

std::shared_ptr<Vision> front_sensor;
std::shared_ptr<Vision> back_sensor;

void init() {
	front_sensor = std::make_shared<Vision>(10);
	back_sensor = std::make_shared<Vision>(16);

	vision_signature_s_t SIG_RED_FRONT = Vision::signature_from_utility(
	    1, 2047, 8241, 5144, -655, 343, -156, 1.000, 0);
	vision_signature_s_t SIG_RED_BACK = Vision::signature_from_utility(
	    1, 4343, 7021, 5682, -1209, -199, -704, 1.700, 0);

	front_sensor->set_signature(1, &SIG_RED_FRONT);
	front_sensor->set_exposure(80);
	back_sensor->set_signature(1, &SIG_RED_BACK);
	back_sensor->set_exposure(48);
}

bool detectBall(bool front = true) {
	int num = 6;

	vision_object_s_t object_arr[num];
	if (front) {
		front_sensor->read_by_sig(0, 1, num, object_arr);
	} else {
		back_sensor->read_by_sig(0, 1, num, object_arr);
	}

	for (int i = 0; i < num; i++) {
		if (front) {
			if ((object_arr[i].x_middle_coord >= target - 60 &&
			     object_arr[i].x_middle_coord <= target + 60) &&
			    object_arr[i].y_middle_coord >= 170)
				return true;
		} else {
			if ((object_arr[i].x_middle_coord >= target - 60 &&
			     object_arr[i].x_middle_coord <= target + 60) &&
			    object_arr[i].y_middle_coord >= 170)
				return true;
		}
	}

	return false;
}

bool checkBeforeRunning(bool front = true) {
	int num = 6;
	vision_object_s_t object_arr[num];
	if (front) {
		return front_sensor->read_by_sig(0, 1, num, object_arr) != 0;
	} else {
		return (back_sensor->read_by_sig(0, 1, num, object_arr) != 0)
		           ? object_arr[0].y_middle_coord <= 100
		           : false;
	}
}

void alignRedFront(bool useActuation, int timeDelay,
                   int base_speed) { // x 120 - 180 y 180 - 211

	/*
	for (int i = 0; i < 3; i++) {
	  if (!checkBeforeRunning())
	    return;
	  delay(10);
	}
	*/

	int pe = 0;

	if (useActuation) {
		intake::open();
	}
	intake::move(100);

	while (!detectBall()) {
		int x_pos = front_sensor->get_by_sig(0, 1)
		                .x_middle_coord; // 0 = largest object, 1 = id
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

void alignRedBack(int timeDelay, int base_speed) {

	for (int i = 0; i < 3; i++) {
		if (!checkBeforeRunning(false))
			return;
		delay(10);
	}

	int pe = 0;
	intake::move(100);

	while (!detectBall(false)) {
		int x_pos = back_sensor->get_by_sig(0, 1)
		                .x_middle_coord; // 0 = largest object, 1 = id
		int error = target - x_pos;
		int derivative = error - pe;
		int speed = error * kp_red + derivative * kd_red;
		pe = error;

		if (x_pos == 0)
			speed = 0;

		chassis::tank(-base_speed + speed, -base_speed - speed);

		delay(10);
	}
	chassis::tank(-base_speed, -base_speed);

	delay(timeDelay);

	chassis::tank(0, 0);
}

} // namespace vision
