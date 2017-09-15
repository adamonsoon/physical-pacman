#include <Player.h>

Player player = (Player) {
  .pos = (BoardSquare) {
    .x = 0,
    .y = 0
  },
  .state = 0,
  .prevDir = directions.none,
  .currentDir = directions.none
};

Player& getPlayer() {
  return player;
}

void setInitialPlayerPosition(BoardSquare s, int dir) {
  player.pos.x = s.x;
  player.pos.y = s.y;
  setPlayerPosition(player.pos, dir, false);
}

void movePlayer(int dir) {
  if (!canMove(millis(), getPreviousMove())) {
    return;
  }
  BoardSquare nextPosition;
  nextPosition = setNextPosition(player.pos, dir);
  player.pos.x = nextPosition.x;
  player.pos.y = nextPosition.y;
  #if DEBUG
    #if OUTPUT_BOARD
      outputBoard();
    #endif
  #endif
}
