#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "pros/misc.h"

namespace intake {

okapi::MotorGroup roller_motors = {-17, 19};
okapi::MotorGroup actuation_motors = {11, -20};
bool intakes_open;

void init() {
	roller_motors.setGearing(okapi::AbstractMotor::gearset::green);
	roller_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	roller_motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

	actuation_motors.setGearing(okapi::AbstractMotor::gearset::green);
	actuation_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	actuation_motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

	intakes_open = false;
}

void move(int speed) {
	roller_motors.moveVoltage(speed * 120);
}

void open(int position) {
	actuation_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	actuation_motors.moveAbsolute(position, 100);
	intakes_open = true;
}

void close(int power) {
	actuation_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	actuation_motors.moveAbsolute(0, 100);
	if (power > 0)
		actuation_motors.moveVoltage(-power * 120);
	intakes_open = false;
}

void opcontrol() {
	static int speed;

	if (master.get_digital(DIGITAL_R1))
		speed = 100;
	else if (master.get_digital(DIGITAL_X))
		speed = -100;
	else
		speed = 0;

	move(speed);

	if (master.get_digital(DIGITAL_R2) || master.get_digital(DIGITAL_A)) {
		if (!intakes_open) {
			open();
		}
	} else if (intakes_open) {
		close();
	}
}

} // namespace intake
