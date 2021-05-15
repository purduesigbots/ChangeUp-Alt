#ifndef _MACROS_HPP_
#define _MACROS_HPP_

namespace macro {

extern bool scoring;

void stopAll();
void stopRollers();
void score(int shootTime = 670, int flywheel_speed = 100);
void doubleShot();
void intake();
void eject();
void outtake(double max = 100);
void cornerGoal(double angle, int ballCount);
} // namespace macro

#endif
