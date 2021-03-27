#include "sensors.hpp"
#include "main.h"

namespace sensors {

#define BLUE 100
#define RED 20
#define LINE_THRESH 2900

Optical color(13);
ADIAnalogIn line_sensor('a');
ADIUltrasonic ul_side('c', 'd');

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

} // namespace sensors
