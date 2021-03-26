#include "main.h"
#include "sensors.hpp"

namespace flywheel {

int taskState = 0;
int flywheelSpeed = 100;
bool ejectMode = false;

okapi::MotorGroup motors = {-15};

int flywheelTask() {
	int c = 0;
	while (true) {
		if (taskState != 0) {
			motors.moveVoltage(flywheelSpeed * 120);
			if (taskState == 1) { // red
				c += 10;
				if (c == 1000) {
					taskState = 2;
					flywheelSpeed = 60;
				}
				if (sensors::detectBlue() && !macro::scoring) {
					if (ejectMode) {
						move(0);
					} else {
						taskState = 2;
					}
				}
			} else if (taskState == 2) { // blue
				c = 0;
				if (sensors::detectRed()) {
					flywheelSpeed = 0;
					taskState = 3;
				}
			} else if (taskState == 3) {
				if (sensors::detectLine()) {
					indexer::move(0);
					taskState = 0;
				}
			}
		}
		// printf("Task state: %d\n", taskState);
		delay(20);
	}
} // namespace flywheel

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

void setEjectMode(bool newMode) {
	ejectMode = newMode;
}

} // namespace flywheel
