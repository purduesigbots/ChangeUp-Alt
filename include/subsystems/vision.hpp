#ifndef _VISION_H_
#define _VISION_H_

namespace vision {

void init();
void alignRedFront(bool useActuation = true, int timeDelay = 0,
                   int base_speed = 60);
void alignRedBack(int timeDelay = 300, int base_speed = 80);

} // namespace vision

#endif
