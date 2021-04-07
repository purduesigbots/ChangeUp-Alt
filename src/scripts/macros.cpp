#include "main.h"
#include "subsystems/flywheel.hpp"
#include "subsystems/indexer.hpp"
#include "subsystems/sensors.hpp"
#include <array>
namespace macro {

bool scoring = false;

void stopRollers() {
	indexer::move(0);
	flywheel::move(0);
}

void stopAll() {
	intake::move(0);
	stopRollers();
}

void score(double indexer_speed, int shootTime, int flywheel_speed) {
	scoring = true;
	flywheel::setSpeed(flywheel_speed);
	flywheel::setState(1);
	delay(50);
	indexer::move(indexer_speed);
	delay(shootTime);
	indexer::move(50);
	scoring = false;
}

void intake() {
	flywheel::setState(2);
	flywheel::setSpeed(70);
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
	indexer::move(-100);
	flywheel::move(-100);
}

void sideGoalAlign(double angle) {
	while (1) {
		double sv = chassis::angle();
		while (sv > 360)
			sv -= 360;
		while (sv < -360)
			sv += 360;
		double turnSpeed = (angle - sv) * 4;
		chassis::holonomic(0, 0, turnSpeed);
	}
}

void cornerGoalAlign(double angle) {
	double prevAngError = 0;

	double prevStrafeError = 0;
	double totalStrafeError = 0;

	std::array<double, 2> prevOffsets{0, 0};

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

		if (abs(strafeError) < 1) {
			totalStrafeError = 0;
		}

		if (abs(ang_error) < 10) {

			strafeSpeed = strafeError * 3 + (strafeError - prevStrafeError) * 14 +
			              totalStrafeError * 0.3;

			double* min = std::min_element(std::begin(offsets), std::end(offsets));
			if (abs(strafeError) < 5 || *min > 15) {
				forwardSpeed = 60;
			}
		}

		chassis::holonomic(forwardSpeed, strafeSpeed, turnSpeed);

		if (forwardSpeed != 0 && abs((offsets[0] + offsets[1]) / 2) < 11.5) {
			chassis::holonomic(0, 0, 0);
			break;
		}

		prevAngError = ang_error;
		prevStrafeError = strafeError;
		prevOffsets[0] = offsets[0];
		prevOffsets[1] = offsets[1];

		delay(10);
	}
}

} // namespace macro
