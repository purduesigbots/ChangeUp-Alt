#ifndef _VISION_H_
#define _VISION_H_

namespace vision {

void init();
void alignRed(bool useActuation = true, int timeDelay = 0, int base_speed = 60);

} // namespace vision

#endif
