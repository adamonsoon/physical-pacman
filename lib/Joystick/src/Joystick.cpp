#include "Joystick.h"

void initJoy() {
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
}

byte getDirection(Directions directions) {

  if (digitalRead(A0) == 0) {
    return directions.left;
  }

  if (digitalRead(A1) == 0) {
    return directions.right;
  }

  if (digitalRead(A2) == 0) {
    return directions.up;
  }

  if (digitalRead(A3) == 0) {
    return directions.down;
  }

  return directions.none;
}

// byte getDirection(Directions directions) {
//
//   byte x = map(analogRead(JOY_X), 0, 1023, 0, 2);
//   byte y = map(analogRead(JOY_Y), 0, 1023, 0, 2);
//
//   switch (x) {
//     case JOY_LEFT:
//       return directions.left;
//     case JOY_RIGHT:
//       return directions.right;
//   }
//
//   switch (y) {
//     case JOY_UP:
//       return directions.up;
//     case JOY_DOWN:
//       return directions.down;
//   }
//
//   return directions.none;
// }
