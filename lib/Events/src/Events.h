#ifndef EVENTS_H
#define EVENTS_H

#define STATE_IDLE 1
#define STATE_OFF 2
#define STATE_PACMAN_DEFAULT 3
#define STATE_MONSTER_VULNERABLE 4
#define STATE_MONSTER_UNVULNERABLE 8
#define STATE_PACMAN_EATING 5
#define STATE_PACMAN_EATEN 7

struct Event {
  int val1;
  int val2;
  int val3;
};

extern void dispatchEvent(int eventCode, Event eventData);

#endif
