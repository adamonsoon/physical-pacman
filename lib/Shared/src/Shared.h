#ifndef SHARED_H
#define SHARED_H

#include <Arduino.h>

#define PIN_OFFSET 3
#define ON LOW
#define OFF HIGH

#define GAME_INACTIVE 0
#define GAME_ACTIVE   1
#define GAME_SPEED 700

struct BoardMetadata {
  const int columns = 7;
  const int rows = 4;
};

constexpr BoardMetadata boardMetadata;

struct Directions {
  const int none  = 0;
  const int up    = 1;
  const int right = 2;
  const int down  = 3;
  const int left  = 4;
};

constexpr Directions directions;

#endif
