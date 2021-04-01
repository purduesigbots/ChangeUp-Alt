#include "sensors.hpp"
#include "ARMS/chassis.h"
#include "main.h"

namespace sensors {

#define BLUE 100
#define RED 20
#define LINE_THRESH 2900

Optical color(13);
ADIAnalogIn line_sensor('a');
ADIUltrasonic ul_side('g', 'h');
ADIUltrasonic ul_left('c', 'd');
ADIUltrasonic ul_right('e', 'f');

void init() {
	color.set_led_pwm(100);
}

bool detectRed() {
	return (color.get_hue() <= RED);
}

bool detectBlue() {
	return (color.get_hue() >= BLUE);
}

bool detectLine() {
	return (line_sensor.get_value() <= LINE_THRESH);
}

void get_xy_offset(double target_angle) {

	double angle = fmod(chassis::angle(), 360);
	double theta = fabs(angle - target_angle) * M_PI / 180;

	theta = 0; // disregard imu

	double y = ul_right.get_value() / 25.4 * cos(theta);
	double x = ul_left.get_value() / 25.4 * cos(theta);

	printf("%.2f %.2f\n", x, y);
}

} // namespace sensors
