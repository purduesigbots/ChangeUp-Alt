#include "main.h"

namespace intake {

okapi::MotorGroup roller_motors = {-2, 19};
okapi::MotorGroup actuation_motors = {4, -20};
int speed = 0;

void init() {
	roller_motors.setGearing(okapi::AbstractMotor::gearset::green);
	roller_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	roller_motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

	actuation_motors.setGearing(okapi::AbstractMotor::gearset::green);
	actuation_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	actuation_motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	intake::speed = speed;
	roller_motors.moveVoltage(speed * 120);
}

void open(int position) {
	actuation_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	actuation_motors.moveAbsolute(position, 100);
}

void close(int power) {
	actuation_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
	actuation_motors.moveAbsolute(0, 100);
	if (power > 0)
		actuation_motors.moveVoltage(-power * 120);
}

} // namespace intake
