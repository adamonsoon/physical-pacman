#include <Arduino.h>
#include <Shared.h>

#define MAX_TASKS 20

typedef struct Task {
  int pin;
  unsigned long start;
  void (*f)(int, int);
  int val;
  bool done;
} Task;

bool timeUp(unsigned long current, unsigned long previous, unsigned long ttl);

unsigned long getPreviousMove();

bool canMove(unsigned long current, unsigned long previous);

Task* getTasks();

void runTask(int slot);

int addTask(Task task);

void completeTask(int slot);

int getAvailableTaskSlot();

int schedule(int pin, void (*f)(int, int), int val, unsigned long start);

bool runSchedule();
