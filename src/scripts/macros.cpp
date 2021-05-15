#include "macros.hpp"
#include "main.h"
#include "subsystems/sensors.hpp"
#include <array>
namespace macro {

bool scoring = false;

void stopRollers() {
	indexer::move(0);
	flywheel::move(0);
	ejector::move(0);
}

void stopAll() {
	intake::move(0);
	stopRollers();
}

void score(int shootTime, int flywheel_speed) {
	scoring = true;
	flywheel::move(flywheel_speed);
	indexer::move(100);
	ejector::move(100);
	delay(shootTime);
	scoring = false;
}

void doubleShot() {
	score(300);
	scoring = true;
	stopRollers();
	delay(300);
	score(300);
}

void intake() {
	flywheel::move(0);
	intake::move(100);
	indexer::move(60);
	ejector::move(100);
}

void eject() {
	flywheel::move(-100);
	indexer::move(-100);
	ejector::move(-100);
}

void outtake(double max) {
	intake::move(-max);
	ejector::move(20);
	indexer::move(-100);
	flywheel::move(-100);
}

void cornerGoal(double angle, int ballCount) {
	double prevAngError = 0;

	double prevStrafeError = 0;
	double totalStrafeError = 0;

	std::array<double, 2> prevOffsets{0, 0};

	bool startScoring = false;

	double scoreDistance = 13;

	int c = 0;

	while (1) {
		double sv = chassis::angle();
		sv = fmod(sv, 360);

		double ang_error = angle - sv;

		double turnSpeed = ang_error * 3 + (ang_error - prevAngError) * 14;
		double forwardSpeed = 0;
		double strafeSpeed = 0;

		std::array<double, 2> offsets = sensors::get_xy_offset(angle);
		if (offsets[0] == -1) {
			offsets[0] = prevOffsets[0];
		}
		if (offsets[1] == -1) {
			offsets[1] = prevOffsets[1];
		}

		double strafeError = offsets[1] - offsets[0];
		if (abs(strafeError) < 4) {
			totalStrafeError += strafeError;
		} else {
			totalStrafeError = 0;
		}

		if (abs(strafeError) < .5) {
			totalStrafeError = 0;
		}

		if (abs(ang_error) < 10) {

			strafeSpeed = strafeError * 5 + (strafeError - prevStrafeError) * 14 +
			              totalStrafeError * 0.3;

			double* min = std::min_element(std::begin(offsets), std::end(offsets));
			if (abs(strafeError) < 5 || *min > 20) {
				forwardSpeed = 60;
			}
		}

		chassis::holonomic(forwardSpeed, strafeSpeed, turnSpeed);

		double distance = abs((offsets[0] + offsets[1]) / 2);
		if (forwardSpeed != 0) {
			if (distance < scoreDistance && !startScoring) {
				startScoring = true;
				pros::Task task{[=] {
					if (ballCount == 1) {
						score(400);
					} else if (ballCount == 2) {
						doubleShot();
					}
				}};
			}
			if (distance < 11.5) {
				chassis::holonomic(0, 0, 0);
				if (!scoring && startScoring)
					break;
			}
		}

		prevAngError = ang_error;
		prevStrafeError = strafeError;
		prevOffsets[0] = offsets[0];
		prevOffsets[1] = offsets[1];

		delay(10);
		c += 10;
		if (c > 3000) {
			break;
		}
	}
}

} // namespace macro
