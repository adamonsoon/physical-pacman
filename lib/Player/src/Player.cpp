#include <Player.h>
#include <Scheduler.h>

Player player = (Player) {
  .pos = (BoardSquare) {
    .x = 0,
    .y = 0
  },
  .state     = STATE_NORMAL,
  .prevDir   = directions.none,
  .currentDir = directions.none
};

Player& getPlayer() {
  return player;
}

void setInitialPlayerPosition(BoardSquare* s, byte dir) {
  player.pos.x = s->x;
  player.pos.y = s->y;
  setPlayerPosition(&player.pos, dir, false);
}

void setPlayerState(byte state, bool shouldDispatch) {
  Serial.println("new player state: " + String(state));

  player.state = state;

  if (shouldDispatch) {
    switch(state) {
      case STATE_NORMAL:
        dispatchEvent(PACMAN,  STATE_PACMAN_DEFAULT);
        break;
      case STATE_POWER_UP:
        dispatchEvent(PACMAN, STATE_PACMAN_EATING);
        break;
    }
  }
}

void handlePowerUp() {
  setPlayerState(STATE_POWER_UP, true);
  setEnemyState(STATE_ENEMIES_VULNURABLE, true);

  scheduleVirtual(setPlayerState, STATE_NORMAL, true, millis() + 10000);
  scheduleVirtual(setEnemyState,  STATE_ENEMIES_WEAK, true, millis() + 5000);
  scheduleVirtual(setEnemyState,  STATE_ENEMIES_NORMAL, true, millis() + 10000);
}

void movePlayer(byte dir) {
  if (!canMove(millis(), getPreviousMove())) {
    return;
  }
  BoardSquare nextPosition;
  nextPosition = getNextPosition(&player.pos, dir);
  if (getPosValue(&nextPosition) == POWER_UP) {
    handlePowerUp();
  }
  nextPosition = setNextPosition(&player.pos, dir);
  player.pos.x = nextPosition.x;
  player.pos.y = nextPosition.y;
  #if DEBUG
    #if OUTPUT_BOARD
      outputBoard();
    #endif
  #endif
}
