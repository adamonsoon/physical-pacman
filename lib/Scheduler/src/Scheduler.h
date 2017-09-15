#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>
#include <Shared.h>

#define MAX_TASKS 30

typedef struct Task {
  int pin;
  PinData pinData;
  unsigned long start;
  void (*f)(int, int);
  int val;
  bool done;
} Task;

extern bool timeUp(unsigned long current, unsigned long previous, unsigned long ttl);

extern unsigned long getPreviousMove();

extern bool canMoveGhost(unsigned long current, unsigned long previous);

extern bool canMove(unsigned long current, unsigned long previous);

extern Task* getTasks();

extern void runTask(int slot);

extern int addTask(Task task);

extern void completeTask(int slot);

extern int getAvailableTaskSlot();

extern int schedule(int pin, void (*f)(int, int), int val, unsigned long start);

extern int schedule(PinData pin, void (*f)(int, int), int val, unsigned long start);

extern bool runSchedule();

#endif
