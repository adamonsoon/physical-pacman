#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "Shared.h"

#define JOY_X 0
#define JOY_Y 1
#define JOY_NONE 1
#define JOY_UP 0
#define JOY_DOWN 2
#define JOY_LEFT 0
#define JOY_RIGHT 2

extern int getDirection(Directions directions);

#endif
