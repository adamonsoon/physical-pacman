#ifndef SHARED_H
#define SHARED_H

#define DEBUG 1
#define OUTPUT_BOARD 1

#include <Arduino.h>

#define NUMBER_OF_PINS 16
#define NUMBER_OF_SHIFT_REGISTERS 2
#define PIN_OFFSET 1
#define ON LOW
#define OFF HIGH

#define GAME_INACTIVE 0
#define GAME_ACTIVE   1
#define GAME_SPEED 300

bool gameActive = GAME_ACTIVE;

struct BoardMetadata {
  const int columns = 19;
  const int rows = 28;
};

constexpr BoardMetadata boardMetadata;

struct PinData {
  int x, y;
  int pin;
  int state;
};

struct Directions {
  const int none  = 0;
  const int up    = 1;
  const int right = 2;
  const int down  = 3;
  const int left  = 4;
};

constexpr Directions directions;

#endif
