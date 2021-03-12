#include "sensors.hpp"
#include "main.h"

namespace sensors {

#define LINE_THRESHOLD 2850

#define BLUE 100
#define RED 20

ADIAnalogIn back_line_sensor('b');
ADIAnalogIn front_line_sensor('a');

Optical color(2);

void init() {
	color.set_led_pwm(100);
}

bool frontLineDetect() {
	return (front_line_sensor.get_value() < LINE_THRESHOLD);
}

bool backLineDetect() {
	return (back_line_sensor.get_value() < LINE_THRESHOLD);
}

bool detectRed() {
	return (color.get_hue() <= RED);
}

bool detectBlue() {
	return (color.get_hue() >= BLUE);
}

} // namespace sensors
