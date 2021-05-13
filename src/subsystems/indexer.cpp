#include "main.h"

namespace indexer {

okapi::MotorGroup motors = {-3};
int speed = 0;

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	indexer::speed = speed;
	motors.moveVoltage(speed * 120);
}

} // namespace indexer
