#include "main.h"

namespace indexer {

okapi::MotorGroup motors = {-3};

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	motors.moveVelocity(speed * 2);
}

void opcontrol() {
	static int speed;

	if (master.get_digital(DIGITAL_L1))
		speed = 100;
	else if (master.get_digital(DIGITAL_L2))
		speed = -100;
	else if (master.get_digital(DIGITAL_R1) &&
	         !(sensors::detectRed() && sensors::detectLine()))
		speed = 50;
	else
		speed = 0;

	move(speed);
}

} // namespace indexer
