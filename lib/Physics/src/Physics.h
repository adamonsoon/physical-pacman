#ifndef PHYSICS_H
#define PHYSICS_H

#include <Arduino.h>
#include <Shared.h>

struct Physics {
  const int numberOfPulses = 5;
  const int timeToReject   = 100;
  const int timeToRest     = 30;
  const bool isOn          = LOW;
  const bool isOff         = HIGH;
  int pinOffset            = 3;
  int minPin               = 1;
  int maxPin               = 20;
  int pinMap[boardMetadata.columns][boardMetadata.rows] = {
    { 15,  16,  17,  18 },
    { 14,  0,   0,   19 },
    { 13,  0,   0,   20 },
    { 12,  1,   2,   3  },
    { 11,  0,   0,   4  },
    { 10,  0,   0,   5  },
    { 9,   8,   7,   6  }
  };
};

extern Physics getPhysics();

extern void initPins();

extern void sendPulse(int pin);

extern int getPin(int c, int r);

extern void blockLeftRight(int c, int r);

extern void blockTopBottom(int c, int r);

#endif
