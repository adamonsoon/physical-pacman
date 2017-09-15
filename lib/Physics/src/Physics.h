#ifndef PHYSICS_H
#define PHYSICS_H

#include <Arduino.h>
#include <Shared.h>

struct Physics {
  const int numberOfPulses   = 5;
  const int timeToReject     = GAME_SPEED;
  const int timeToRest       = 30;
  const bool isOn            = ON;
  const bool isOff           = OFF;
  int pinOffset              = PIN_OFFSET;
  int minPin                 = 1;
  int maxPin                 = 16;
  int numberOfPins           = NUMBER_OF_PINS;
  int numberOfShiftRegisters = NUMBER_OF_SHIFT_REGISTERS;
  // int pinMap[boardMetadata.columns][boardMetadata.rows] = {
  //   { 15,  16,  17,  18 },
  //   { 14,  0,   0,   19 },
  //   { 13,  0,   0,   20 },
  //   { 12,  1,   2,   3  },
  //   { 11,  0,   0,   4  },
  //   { 10,  0,   0,   5  },
  //   { 9,   8,   7,   6  }
  // };
  byte pinMap[boardMetadata.columns][boardMetadata.rows];
  // = {
  //   { 10,  9,   8,   7,  6 },
  //   { 11,  0,   0,   0,  5 },
  //   { 12,  0,   0,   0,  4 },
  //   { 13,  0,   0,   0,  3 },
  //   { 14,  0,   0,   0,  2 },
  //   { 15,  16,  17,  2,  1 }
  // };
  PinData stateMap[boardMetadata.columns][boardMetadata.rows];

};

extern Physics getPhysics();

extern void initPins();

extern void setPinMode(int pin, int mode);

extern void setPinMode(PinData pin, int mode);

extern void sendPulse(int pin, int delay, void (*setPinMode)(int, int) = setPinMode);

extern void sendPulse(PinData pin, int delay, void (*setPinMode)(int, int) = setPinMode);

extern PinData getPin(int c, int r);

#endif
