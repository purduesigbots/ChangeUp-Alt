#ifndef _VISION_H_
#define _VISION_H_

namespace vision {

void init();
void alignFront(int sig, int timeDelay = 0, int base_speed = 60,
                bool useActuation = true);
void alignBack(int sig, int timeDelay = 250, int base_speed = 60);

} // namespace vision

#endif
