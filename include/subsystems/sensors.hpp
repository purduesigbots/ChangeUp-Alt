#ifndef _SENSORS_H_
#define _SENSORS_H_

namespace sensors {

void init();

bool frontLineDetect();
bool backLineDetect();

bool detectRed();
bool detectBlue();

} // namespace sensors
#endif
