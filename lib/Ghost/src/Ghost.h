#ifndef GHOST_H
#define GHOST_H

#include <Shared.h>
#include <Board.h>
#include <Scheduler.h>

#define STATE_NORMAL 0
#define STATE_VULNURABLE 1
#define STATE_INVISIBLE 2

struct Ghost {
  BoardSquare pos;
  int state;
  int prevDir;
  int currentDir;
  int identifier;
  unsigned long previousMove;
};

extern Ghost& getRandomGhost();

extern int getRandomGhostMove();

extern void moveGhost(int identifier);

extern void setGhostPosition(BoardSquare s, int dir, bool pulse, int identifier);

extern void setRandomGhostPosition(BoardSquare s, int dir, bool pulse, int identifier);

#endif
