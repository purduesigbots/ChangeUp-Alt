#ifndef _MACROS_HPP_
#define _MACROS_HPP_

namespace macro {

extern bool scoring;

void stopRollers();
void stopAll();
void score(double indexer_speed = 80, int shootTime = 400,
           int flywheel_speed = 100);
void intake();
void eject();
void intakeBlue();
void outtake(double max = 100);
void sideGoal(double angle);
void cornerGoal(double angle, int ballCount);

} // namespace macro

#endif
