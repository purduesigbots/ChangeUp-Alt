#include "sensors.hpp"
#include "ARMS/chassis.h"
#include "main.h"

namespace sensors {

#define BLUE 100
#define RED 20
#define LINE_THRESH 2900

Optical color(13);
ADIAnalogIn line_sensor('a');
ADIUltrasonic ul_side('c', 'd');
ADIUltrasonic ul_left('g', 'h');
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

int read_ul_side() {
	return ul_side.get_value();
}

void get_xy_offset(double target_angle) {

	double angle = fmod(chassis::angle(), 360);
	double theta = fabs(angle - target_angle) * M_PI / 180;

	double x = ul_right.get_value() / 25.4 * cos(theta);
	double y = ul_left.get_value() / 25.4 * cos(theta);

	printf("%d %d %lf %lf %lf\n", ul_right.get_value(), ul_left.get_value(), x, y,
	       theta);
}

} // namespace sensors
