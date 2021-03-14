#include "sensors.hpp"
#include "main.h"

namespace sensors {

#define BLUE 100
#define RED 20

Optical color(2);

void init() {
	color.set_led_pwm(100);
}

bool detectRed() {
	return (color.get_hue() <= RED);
}

bool detectBlue() {
	return (color.get_hue() >= BLUE);
}

} // namespace sensors
