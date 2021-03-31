#ifndef _SENSORS_H_
#define _SENSORS_H_

namespace sensors {

void init();

bool detectRed();
bool detectBlue();
bool detectLine();
int read_ul_side();
void get_xy_offset(double target_angle);

} // namespace sensors
#endif
