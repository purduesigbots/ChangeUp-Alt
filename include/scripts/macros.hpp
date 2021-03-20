#ifndef _MACROS_HPP_
#define _MACROS_HPP_

namespace macro {

extern bool scoring;

void stopRollers();
void stopAll();
void score(double indexer_speed = 80, int shootTime = 400,
           int flywheel_speed = 100);
void intake(bool with_indexer = true);
void intakeBlue();
void outtake(double max = 100);

} // namespace macro

#endif
