#ifndef PHYSICS_H
#define PHYSICS_H

#include <Arduino.h>
#include <Shared.h>

struct Physics {
  const byte numberOfPulses   = 5;
  const int timeToReject     = GAME_SPEED;
  const byte timeToRest       = 30;
  const bool isOn             = ON;
  const bool isOff            = OFF;
  byte pinOffset              = PIN_OFFSET;
  byte minPin                 = 1;
  byte maxPin                 = 16;
  byte numberOfPins           = NUMBER_OF_PINS;
  byte numberOfShiftRegisters = NUMBER_OF_SHIFT_REGISTERS;
  // byte pinMap[boardMetadata.columns][boardMetadata.rows] = {
  //   { 15,  16,  17,  18 },
  //   { 14,  0,   0,   19 },
  //   { 13,  0,   0,   20 },
  //   { 12,  1,   2,   3  },
  //   { 11,  0,   0,   4  },
  //   { 10,  0,   0,   5  },
  //   { 9,   8,   7,   6  }
  // };
  byte layout[boardMetadata.columns][boardMetadata.rows] = {
    { 15, 22, 29, 40, 45, 50, 65, 69, 73, 88, 94, 100, 113, 117, 121, 134, 140, 144, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY    },
    { 14, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   112, 0,   0,   133, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  EMPTY    },
    { 13, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   111, 0,   0,   132, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  EMPTY    },
    { 12, 21, 28, 39, 44, 49, 64, 0,  0,  87, 93, 99,  110, 0,   0,   131, 139, 143, EMPTY, 0,  0,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, POWER_UP },
    { 0,  0,  0,  38, 0,  0,  63, 0,  0,  86, 0,  0,   0,   0,   0,   0,   0,   0,  EMPTY, 0,  0,  EMPTY, 0,  0,  EMPTY, 0,  0,  0     },
    { 0,  0,  0,  37, 0,  0,  62, 0,  0,  85, 0,  0,   0,   0,   0,   0,   0,   0,  EMPTY, 0,  0,  EMPTY, 0,  0,  EMPTY, 0,  0,  0     },
    { 11, 20, 27, 36, 0,  0,  61, 68, 72, 84, 92, 98,  109, 116, 120, 130, 138, 142, EMPTY, EMPTY, EMPTY, EMPTY, 0,  0,  EMPTY, EMPTY, EMPTY, EMPTY    },
    { 10, 0,  0,  0,  0,  0,  60, 0,  0,  83, 0,  0,   108, 0,   0,   129, 0,   0,  EMPTY,  0, 0,  EMPTY, 0,  0,  0,  0,  0,  EMPTY    },
    { 9,  0,  0,  0,  0,  0,  59, 0,  0,  82, 0,  0,   107, 0,   0,   128, 0,   0,  EMPTY,  0, 0,  EMPTY, 0,  0,  0,  0,  0,  EMPTY    },
    { 8,  19, 26, 35, 43, 48, 58, 0,  0,  81, 0,  0,   106, 0,   0,   127, 0,   0,  0,,  0, 0,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY    },
    { 7,  0,  0,  0,  0,  0,  57, 0,  0,  80, 0,  0,   0,   0,   0,   0,   0,   0,  EMPTY,  0, 0,  EMPTY, 0,  0,  0,  0,  0,  EMPTY    },
    { 6,  0,  0,  0,  0,  0,  56, 0,  0,  79, 0,  0,   0,   0,   0,   0,   0,   0,  EMPTY,  0, 0,  EMPTY, 0,  0,  0,  0,  0,  EMPTY    },
    { 5,  18, 25, 34, 0,  0,  55, 67, 71, 78, 91, 97,  105, 115, 119, 126, 137, 141, EMPTY, EMPTY, EMPTY, EMPTY, 0,  0,  EMPTY, EMPTY, EMPTY, EMPTY    },
    { 0,  0,  0,  33, 0,  0,  54, 0,  0,  77, 0,  0,   0,   0,   0,   0,   0,   0,  EMPTY, 0,  0,  EMPTY, 0,  0,  EMPTY, 0,  0,  0     },
    { 0,  0,  0,  32, 0,  0,  53, 0,  0,  76, 0,  0,   0,   0,   0,   0,   0,   0,  EMPTY, 0,  0,  EMPTY, 0,  0,  EMPTY, 0,  0,  0     },
    { 4,  17, 24, 31, 42, 47, 52, 0,  0,  75, 90, 96,  104, 0,   0,   125, 136, 140, EMPTY, 0,  0,  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, POWER_UP },
    { 3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   103, 0,   0,   124, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  EMPTY    },
    { 2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   102, 0,   0,   123, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  EMPTY    },
    { 1,  16, 23, 30, 41, 46, 51, 66, 70, 74, 89, 95,  101, 114, 118, 122, 135, 141, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY    }
    };
  PinData stateMap[boardMetadata.columns][boardMetadata.rows];

};

extern Physics getPhysics();

extern void initPins();

extern void setPinMode(byte pin, byte mode);

extern void setPinMode(PinData pin, byte mode);

extern void sendPulse(byte pin, byte delay, void (*setPinMode)(byte, byte) = setPinMode);

extern void sendPulse(PinData pin, byte delay, void (*setPinMode)(byte, byte) = setPinMode);

extern PinData getPin(byte c, byte r);

#endif
