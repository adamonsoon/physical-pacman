#ifndef PLAYER_H
#define PLAYER_H

#include <Shared.h>
#include <Board.h>
#include <Scheduler.h>
#include <Events.h>

#define STATE_NORMAL 0
#define STATE_POWER_UP 1
#define STATE_DEAD 2

struct Player {
  BoardSquare pos;
  byte state;
  byte prevDir;
  byte currentDir;
};

extern void setInitialPlayerPosition(BoardSquare* s, byte dir);

extern Player& getPlayer();

extern void movePlayer(byte dir);

#endif
