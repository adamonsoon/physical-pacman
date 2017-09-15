#ifndef PLAYER_H
#define PLAYER_H

#include <Shared.h>
#include <Board.h>
#include <Scheduler.h>

#define STATE_NORMAL 0
#define STATE_POWER_UP 1
#define STATE_DEAD 2

struct Player {
  BoardSquare pos;
  int state;
  int prevDir;
  int currentDir;
};

extern void setInitialPlayerPosition(BoardSquare s, int dir);

extern Player& getPlayer();

extern void movePlayer(int dir);

#endif
