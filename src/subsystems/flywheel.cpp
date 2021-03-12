#include "main.h"
#include "sensors.hpp"

namespace flywheel {

int taskState = 0;
int flywheelSpeed = 100;

okapi::MotorGroup motors = {-7};

int flywheelTask() {
	while (true) {
		if (taskState != 0) {
			motors.moveVoltage(flywheelSpeed * 120);
			if (taskState == 1) { // red
				if (sensors::detectBlue() && !macro::scoring) {
					taskState = 2;
					flywheelSpeed = 70;
				}
			} else if (taskState == 2) { // blue
				if (sensors::detectRed()) {
					motors.moveVoltage(0);
					taskState = 0;
				}
			}
		}
		printf("Task state: %d\n", taskState);
		delay(20);
	}
}

void init() {
	motors.setGearing(okapi::AbstractMotor::gearset::green);
	motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

	Task flywheel_task(flywheelTask);
}

void move(int speed) {
	motors.moveVoltage(speed * 120);
	taskState = 0;
}

void opcontrol() {
	static int speed;

	if (master.get_digital(DIGITAL_L1))
		speed = 100;
	else if (master.get_digital(DIGITAL_L2))
		speed = -100;
	else
		speed = 0;

	move(speed);
}

void setSpeed(int speed) {
	flywheelSpeed = speed;
}

void setState(int newState) {
	taskState = newState;
}

int getState() {
	return taskState;
}

} // namespace flywheel
