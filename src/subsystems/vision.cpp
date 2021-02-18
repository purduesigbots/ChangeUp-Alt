#include "ARMS/chassis.h"
#include "main.h"

const int target = 165;
const double kp_red = .4;
const double kd_red = .8;
const double kp_blue = .6;
const double kd_blue = .8;
const int minimum = 450;

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

void alignRed() {

	int pe = 0;
	int count = 0;

	while (true) {
		int x_pos =
		    sensor->get_by_sig(0, 1).x_middle_coord; // 0 = largest object, 1 = id
		int error = target - x_pos;
		int derivative = error - pe;
		int speed = error * kp_red + derivative * kd_red;
		pe = error;

		chassis::tank(-speed, speed);

		if (count < minimum) {
			count += 10;
		} else if (chassis::settled()) {
			break;
		}

		delay(10);
	}

	intake::move(100);

	while (sensor->get_by_sig(0, 1).top_coord < 180) {
		chassis::tank(60, 60);
	}

	chassis::tank(0, 0);
	intake::move(0);
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
