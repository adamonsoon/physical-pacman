/**
  Shared State
**/
#ifndef SHARED_H
#define SHARED_H

#define DEBUG 1
#define OUTPUT_BOARD 1

#include <Arduino.h>
#include <Events.h>

#define NUMBER_OF_PINS 16
#define NUMBER_OF_SHIFT_REGISTERS 23
#define PIN_OFFSET 1
#define ON LOW
#define OFF HIGH

#define GAME_INACTIVE 0
#define GAME_ACTIVE   1
#define GAME_SPEED  300

#define TAIL_LENGTH 2
#define WALL        1
#define EMPTY       0
#define PACMAN      2
#define POWER_UP    3
#define PINKY       4
#define CLYDE       5
#define ENEMIES     9

#define STATE_ENEMIES_NORMAL     0
#define STATE_ENEMIES_VULNURABLE 1
#define STATE_ENEMIES_WEAK       2

struct BoardMetadata {
  const byte columns = 19;
  const byte rows = 28;
};

constexpr BoardMetadata boardMetadata;

struct PinData {
  byte x, y;
  byte pin;
  byte state;
};

struct Directions {
  const byte none  = 0;
  const byte up    = 1;
  const byte right = 2;
  const byte down  = 3;
  const byte left  = 4;
};

constexpr Directions directions;

extern void setGameActive();

extern void setGameInactive();

extern bool isGameActive();

extern void pacmanDied(byte identifier);

#endif
