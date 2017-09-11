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

int getAvailableTaskSlot() {
  for (int s = 0; s < MAX_TASKS; s++) {
    if (tasks[s].pin == 0 || tasks[s].done == true) {
      return s;
    }
  }
  return -1;
}

void completeTask(int slot) {
  tasks[slot].done = true;
}

void runTask(int slot) {
  Task task = tasks[slot];
  task.f(task.pin, task.val);
  completeTask(slot);
}

int addTask(Task task) {
  int slot = getAvailableTaskSlot();
  if (slot != -1) {
    tasks[slot] = task;
  }
  return slot;
}

int schedule(int pin, void (*f)(int, int), int val, unsigned long start) {
  Task task;
  task.pin      = pin;
  task.start    = start;
  task.val      = val;
  task.f        = f;
  task.done     = false;
  return addTask(task);
}

bool shouldRunTask(Task task, unsigned long current) {
  return task.done == false &&
  task.pin != 0 &&
  current >= task.start;
}

bool runSchedule() {
  bool tasksRun = false;
  unsigned long current = millis();
  for (int s = 0; s < MAX_TASKS; s++) {
    if (shouldRunTask(tasks[s], current)) {
      tasksRun = true;
      runTask(s);
    }
  }
  return tasksRun;
}
