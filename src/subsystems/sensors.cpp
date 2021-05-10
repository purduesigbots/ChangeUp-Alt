#include "sensors.hpp"
#include "ARMS/chassis.h"
#include "main.h"
#include "pros/distance.hpp"
#include <array>

namespace sensors {

#define BLUE 100
#define RED 40

// Optical color(5);
ADIAnalogIn line_sensor('a');
ADIUltrasonic ul_left('g', 'h');
ADIUltrasonic ul_right('e', 'f');

void init() {
	// color.set_led_pwm(100);
}

// bool red() {
// 	return (color.get_hue() <= RED);
// }

// bool blue() {
// 	return (color.get_hue() >= BLUE);
// }

bool line() {
	return (line_sensor.get_value() <= 2900);
}

std::array<double, 2> get_xy_offset(double target_angle) {

	double angle = fmod(chassis::angle(), 360);
	double theta = fabs(angle - target_angle) * M_PI / 180;

	theta = 0; // disregard imu

	double y = ul_right.get_value() / 25.4 * cos(theta);
	double x = ul_left.get_value() / 25.4 * cos(theta);

	return std::array<double, 2>{x, y};
}

} // namespace sensors
