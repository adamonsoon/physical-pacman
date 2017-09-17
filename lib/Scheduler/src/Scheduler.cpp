#include <Scheduler.h>

Task tasks[MAX_TASKS];

unsigned long previousMove = 0;

bool timeUp(unsigned long current, unsigned long previous, unsigned long interval) {
  return (current - previous >= interval);
}

unsigned long getPreviousMove() {
  return previousMove;
}

void setPreviousMove(unsigned long previous) {
  previousMove = previous;
}

bool canMoveGhost(unsigned long current, unsigned long previous) {
  bool moveAvailable = timeUp(current, previous, GAME_SPEED);
  return moveAvailable;
}

bool canMove(unsigned long current, unsigned long previous) {
  bool moveAvailable = timeUp(current, previous, GAME_SPEED);
  if (moveAvailable) {
    setPreviousMove(current);
  }
  return moveAvailable;
}

Task* getTasks() {
  return tasks;
}

byte getAvailableTaskSlot() {
  for (byte s = 0; s < MAX_TASKS; s++) {
    if (tasks[s].pin == 0 || tasks[s].done == true) {
      return s;
    }
  }
  return -1;
}

void completeTask(Task* task) {
  task->done = true;
}

void runTask(Task* task) {
  if (task->isVirtual) {
    task->v(task->val, task->val2);
  } else {
    task->f(task->pin, task->val);
  }
  completeTask(task);
}

byte schedule(byte pin, void (*f)(byte, byte), byte val, unsigned long start) {
  byte slot = getAvailableTaskSlot();
  if (slot != -1) {
    tasks[slot].pin   = pin;
    tasks[slot].start = start;
    tasks[slot].val   = val;
    tasks[slot].f     = f;
    tasks[slot].done  = false;
  }
  return slot;
}

byte schedule(PinData pin, void (*f)(byte, byte), byte val, unsigned long start) {
  byte slot = getAvailableTaskSlot();
  if (slot != -1) {
    tasks[slot].pinData = pin;
    tasks[slot].start   = start;
    tasks[slot].val     = val;
    tasks[slot].f       = f;
    tasks[slot].done    = false;
  }
  return slot;
}

byte scheduleVirtual(void (*v)(byte, bool), byte val, byte val2, unsigned long start) {
  byte slot = getAvailableTaskSlot();
  if (slot != -1) {
    tasks[slot].isVirtual = true;
    tasks[slot].start     = start;
    tasks[slot].val       = val;
    tasks[slot].val2      = val2;
    tasks[slot].v         = v;
    tasks[slot].done    = false;
  }
  return slot;
}

bool shouldRunTask(Task* task, unsigned long current) {
  if (task->isVirtual) {
    return task->done == false &&
    current >= task->start;
  }
  return task->done == false &&
  task->pin != 0 &&
  current >= task->start;
}

bool runSchedule() {
  bool tasksRun = false;
  unsigned long current = millis();
  for (byte s = 0; s < MAX_TASKS; s++) {
    if (shouldRunTask(&tasks[s], current)) {
      tasksRun = true;
      runTask(&tasks[s]);
    }
  }
  return tasksRun;
}
