#ifndef GHOST_H
#define GHOST_H

#include <Shared.h>
#include <Board.h>
#include <Scheduler.h>

#define PINKY 4
#define CLYDE 5

#define STATE_GHOST_DEFAULT 0
#define STATE_GHOST_VULNURABLE 1
#define STATE_GHOST_INVISIBLE 2

struct Ghost {
  BoardSquare pos;
  byte state;
  byte prevDir;
  byte currentDir;
  byte identifier;
  unsigned long previousMove;
};

extern Ghost& getPinky();

extern Ghost& getClyde();

extern void setGhostPosition(BoardSquare* s, byte dir, bool pulse, Ghost& ghost);

extern byte getGhostMove(Ghost& ghost);

extern void moveGhost(Ghost& ghost);

#endif
