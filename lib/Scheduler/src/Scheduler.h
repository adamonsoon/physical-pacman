#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>
#include <Shared.h>

#define MAX_TASKS 30

typedef struct Task {
  byte pin;
  bool isVirtual;
  PinData pinData;
  unsigned long start;
  void (*f)(byte, byte);
  void (*v)(byte, bool);
  byte val;
  byte val2;
  bool done;
} Task;

extern bool timeUp(unsigned long current, unsigned long previous, unsigned long ttl);

extern unsigned long getPreviousMove();

extern bool canMoveGhost(unsigned long current, unsigned long previous);

extern bool canMove(unsigned long current, unsigned long previous);

extern Task* getTasks();

extern void runTask(Task* task);

extern void completeTask(Task* task);

extern byte getAvailableTaskSlot();

extern byte scheduleVirtual(void (*v)(byte, bool), byte val, byte val2, unsigned long start);

extern byte schedule(byte pin, void (*f)(byte, byte), byte val, unsigned long start);

extern byte schedule(PinData pin, void (*f)(byte, byte), byte val, unsigned long start);

extern bool runSchedule();

#endif
