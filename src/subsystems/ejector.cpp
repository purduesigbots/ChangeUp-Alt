#include "main.h"

namespace ejector {

okapi::MotorGroup motors = {17};

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::blue);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	motors.moveVoltage(speed * 120);
}

void opcontrol() {
	static int speed;

	if (master.get_digital(DIGITAL_L1))
		speed = 100;
	else if (master.get_digital(DIGITAL_X))
		speed = -100;
	else if (master.get_digital(DIGITAL_R1) &&
	         !(sensors::detectRed() && sensors::detectLine()))
		speed = 100;
	else
		speed = 0;

	move(speed);
}

} // namespace ejector
