#include "pros/vision.h"
#include "ARMS/chassis.h"
#include "main.h"
#include "sensors.hpp"

const int frontTarget = 160;
const int backTarget = 145;
const double kp_red = .4;
const double kd_red = .8;
const double kp_blue = .6;
const double kd_blue = .8;
const int minimum = 300;

namespace vision {

vision_signature_s_t signatures[8];

std::shared_ptr<Vision> front_sensor;
std::shared_ptr<Vision> back_sensor;

void init() {
	front_sensor = std::make_shared<Vision>(10);
	back_sensor = std::make_shared<Vision>(16);

	// lab daytime
	signatures[0] = Vision::signature_from_utility(1, 3435, 7005, 5220, -875, 47,
	                                               -414, 2.000, 0);
	signatures[1] = Vision::signature_from_utility(1, 3205, 6485, 4845, -775, 251,
	                                               -262, 1.800, 0);
	signatures[2] = Vision::signature_from_utility(1, 4019, 6761, 5390, -907, 125,
	                                               -391, 2.500, 0);
	signatures[3] = Vision::signature_from_utility(1, 4231, 7047, 5638, -489, 555,
	                                               32, 2.400, 0);
	signatures[4] = Vision::signature_from_utility(1, 4021, 8623, 6322, -421, 477,
	                                               28, 1.700, 0);
	signatures[5] = Vision::signature_from_utility(1, 4723, 7171, 5947, 261, 1157,
	                                               709, 3.200, 0);
	signatures[6] = Vision::signature_from_utility(1, 3905, 6721, 5314, -685, 201,
	                                               -242, 2.700, 0);
	signatures[7] = Vision::signature_from_utility(1, 3905, 6721, 5314, -685, 201,
	                                               -242, 2.700, 0);

	front_sensor->set_exposure(70);
	back_sensor->set_exposure(70);
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
			if ((object_arr[i].x_middle_coord >= frontTarget - 60 &&
			     object_arr[i].x_middle_coord <= frontTarget + 60) &&
			    object_arr[i].y_middle_coord >= 160)
				return true;
		} else {
			if ((object_arr[i].x_middle_coord >= backTarget - 80 &&
			     object_arr[i].x_middle_coord <= backTarget + 80) &&
			    object_arr[i].y_middle_coord >= 190)
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

void alignFront(int sig, int timeDelay, int base_speed,
                bool useActuation) { // x 120 - 180 y 180 - 211

	/*
	for (int i = 0; i < 3; i++) {
	  if (!checkBeforeRunning())
	    return;
	  delay(10);
	}
	*/

	front_sensor->set_signature(1, &signatures[sig]);

	int pe = 0;

	if (useActuation) {
		intake::open();
	}
	intake::move(100);

	while (!detectBall()) {
		int x_pos = front_sensor->get_by_sig(0, 1)
		                .x_middle_coord; // 0 = largest object, 1 = id
		int error = frontTarget - x_pos;
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

void alignBack(int sig, int timeDelay, int base_speed) {

	back_sensor->set_signature(1, &signatures[sig]);

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
		int error = backTarget - x_pos;
		int derivative = error - pe;
		int speed = error * kp_red + derivative * kd_red;
		pe = error;

		if (x_pos == 0)
			speed = 0;

		chassis::tank(-base_speed - speed, -base_speed + speed);

		delay(10);
	}
	chassis::tank(-base_speed, -base_speed);

	delay(timeDelay);

	chassis::tank(0, 0);
}

} // namespace vision
