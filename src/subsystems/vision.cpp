#include "ARMS/chassis.h"
#include "main.h"

const int target = 165;
const double kp = .4;
const double kd = .8;
const int minimum = 300;

namespace vision {

std::shared_ptr<Vision> sensor;

void init() {
	sensor = std::make_shared<Vision>(18);

	vision_signature_s_t SIG = Vision::signature_from_utility(
	    1, 5461, 7963, 6712, -1301, -337, -819, 2.700, 1);

	sensor->set_signature(1, &SIG);
}

void align() {

	int pe = 0;
	int count = 0;

	while (true) {
		int x_pos =
		    sensor->get_by_sig(0, 1).x_middle_coord; // 0 = largest object, 1 = id
		int error = target - x_pos;
		int derivative = error - pe;
		int speed = error * kp + derivative * kd;
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

	while (sensor->get_by_sig(0, 1).top_coord < 150) {
		chassis::tank(60, 60);
	}

	chassis::tank(0, 0);
}

} // namespace vision
