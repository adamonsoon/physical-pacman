#ifndef PHYSICS_H
#define PHYSICS_H

#include <Arduino.h>
#include <Shared.h>

struct Physics {
  const int numberOfPulses = 5;
  const int timeToReject   = 100;
  const int timeToRest     = 30;
  const bool isOn          = ON;
  const bool isOff         = OFF;
  int pinOffset            = PIN_OFFSET;
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

Physics getPhysics();

void initPins();

void sendPulse(int pin);

int getPin(int c, int r);

void blockLeftRight(int c, int r);

void blockTopBottom(int c, int r);

#endif
