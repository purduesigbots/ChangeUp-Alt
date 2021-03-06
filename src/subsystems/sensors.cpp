#include "main.h"

namespace sensors {

#define LINE_THRESHOLD 2850

ADIAnalogIn back_line_sensor('b');
ADIAnalogIn front_line_sensor('a');

bool frontLineDetect() {
	return (front_line_sensor.get_value() < LINE_THRESHOLD);
}

bool backLineDetect() {
	return (back_line_sensor.get_value() < LINE_THRESHOLD);
}

} // namespace sensors
