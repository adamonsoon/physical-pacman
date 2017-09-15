#ifndef EVENTS_H
#define EVENTS_H

#define MAX_EVENTS_QUEUE 10

#define STATE_IDLE 1
#define STATE_OFF 2
#define STATE_PACMAN_DEFAULT 3
#define STATE_MONSTER_VULNERABLE 4
#define STATE_MONSTER_UNVULNERABLE 8
#define STATE_PACMAN_EATING 5
#define STATE_PACMAN_EATEN 7

struct Event {
  int code;
  int data;
};

extern void dispatchOuterEvent(Event event);

extern void dispatchInnerEvent(Event event);

extern void innerEventObserver();

#endif
