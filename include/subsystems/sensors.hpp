#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <array>

namespace sensors {

void init();

bool detectRed();
bool detectBlue();
bool detectLine();
std::array<double, 2> get_xy_offset(double target_angle);

} // namespace sensors
#endif
