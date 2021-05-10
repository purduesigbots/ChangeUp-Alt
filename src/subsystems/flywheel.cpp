#include "main.h"
#include "sensors.hpp"

namespace flywheel {

okapi::MotorGroup motors = {-15};
int speed = 0;

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

void move(int speed) {
	flywheel::speed = speed;
	motors.moveVoltage(speed * 120);
}

} // namespace flywheel
