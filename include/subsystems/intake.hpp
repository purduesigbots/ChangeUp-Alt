#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "okapi/api.hpp"

namespace intake {

extern okapi::MotorGroup roller_motors;
extern int speed;
void init();
void move(int speed);
void open(int position = 120);
void close(int power = 0);

} // namespace intake

#endif
