#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "okapi/api.hpp"

namespace intake {

extern okapi::MotorGroup roller_motors;
extern bool intakes_open;
void init();
void move(int speed);
void open();
void close(int power = 0);
void trigger();
void opcontrol();

} // namespace intake

#endif
