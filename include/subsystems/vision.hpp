#ifndef _VISION_H_
#define _VISION_H_

namespace vision {

void init();
void alignRed(bool useActuation = true, int timeDelay = 200,
              int base_speed = 60);
void alignBlue();

} // namespace vision

#endif
