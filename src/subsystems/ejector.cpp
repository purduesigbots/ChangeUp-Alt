#include "main.h"

namespace ejector {

okapi::MotorGroup motors = {17};
int speed = 0;

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::blue);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	ejector::speed = speed;
	motors.moveVoltage(speed * 120);
}

} // namespace ejector
