#include "Joystick.h"

int getDirection(Directions directions) {

  int x = map(analogRead(JOY_X), 0, 1023, 0, 2);
  int y = map(analogRead(JOY_Y), 0, 1023, 0, 2);

  switch (x) {
    case JOY_LEFT:
      return directions.left;
    case JOY_RIGHT:
      return directions.right;
  }

  switch (y) {
    case JOY_UP:
      return directions.up;
    case JOY_DOWN:
      return directions.down;
  }

  return directions.none;
}
