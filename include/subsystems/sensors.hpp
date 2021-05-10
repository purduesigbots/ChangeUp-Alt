#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <array>

namespace sensors {

void init();

bool red();
bool blue();
bool line();
double getSideDistance();
std::array<double, 2> get_xy_offset(double target_angle);

} // namespace sensors
#endif
