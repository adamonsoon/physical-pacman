#include <Arduino.h>
#include <unity.h>
#include <Shared.h>
#include <Physics.h>
#include <Board.h>
#include <Joystick.h>
#include <Scheduler.h>

#ifdef UNIT_TEST

void setUp(void) {
  initPins();
  Serial.begin(9600);
}

Physics testPhysics = getPhysics();
GameBoard testBoard = getBoard();

void test_relay_pulse(void) {
  for (int i = (testPhysics.minPin + testPhysics.pinOffset); i <= (testPhysics.maxPin + testPhysics.pinOffset); i++) {
    Serial.println(i);
    sendPulse(i, 0);
    runSchedule();
    delay(800);
  }
  runSchedule();
}

void testSetPinMode(int pin, int mode) {
  Serial.println("Setting pin " + String(pin) + " to " + mode);
  setPinMode(pin, mode);
}

void test_pulse(void) {
  unsigned long current = millis();
  int firstPin = (testPhysics.minPin + testPhysics.pinOffset);
  int timeBetween = 100;

  while (millis() < current + 3000) {

    if (millis() == current) {
      sendPulse(firstPin, 0, testSetPinMode);
    }

    if (millis() - timeBetween == current) {
      sendPulse(firstPin + 1, 0, testSetPinMode);
    }

    if (millis() - timeBetween * 2 == current) {
      sendPulse(firstPin + 2, 0, testSetPinMode);
    }

    runSchedule();

  }
}

void test_is_player(void) {
  BoardSquare s;
  s.x = 0;
  s.y = 0;
  setPlayerPosition(s,false);
  TEST_ASSERT_EQUAL_MESSAGE(true, isPlayer(s), "Is Player");
}

void test_is_enemy(void) {
  BoardSquare s;
  s.x = 0;
  s.y = 0;
  setEnemyPosition(s,false);
  TEST_ASSERT_EQUAL_MESSAGE(true, isEnemy(s), "Is Enemy");
}

void test_set_pos_value(void) {
  BoardSquare s;
  s.x = 0;
  s.y = 0;
  setPosValue(s,5);
  TEST_ASSERT_EQUAL_MESSAGE(5, getPosValue(s), "Set and Get 5 in pos 0,0");
}

void test_out_of_bounds(void) {
  BoardSquare s;

  s.x = -1;
  s.y = 0;
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(s), "Column in pos -1");

  s.x = 0;
  s.y = -1;
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(s), "Row in pos -1");

  s.x = boardMetadata.columns;
  s.y = 0;
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(s), "Column at pos c+1");

  s.x = 0;
  s.y = boardMetadata.rows;
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(s), "Row at pos r+1");

  s.x = 0;
  s.y = 0;
  setPosValue(s, testBoard.wall);
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(s), "Set a wall at pos 0,0");
}

void test_time_up(void) {
  TEST_ASSERT_EQUAL_MESSAGE(false, timeUp(100,0,200), "Half time passed");
  TEST_ASSERT_EQUAL_MESSAGE(true, timeUp(100,0,100), "Exact time passed");
  TEST_ASSERT_EQUAL_MESSAGE(true, timeUp(100,0,50), "Access time passed");
}

void test_can_move(void) {
  TEST_ASSERT_EQUAL_MESSAGE(false, canMove(GAME_SPEED - (GAME_SPEED / 2), 0), "1/2 time before");
  TEST_ASSERT_EQUAL_MESSAGE(false, canMove(GAME_SPEED - (GAME_SPEED / 3), 0), "1/3 time before");
  TEST_ASSERT_EQUAL_MESSAGE(true, canMove(GAME_SPEED, 0), "Exact time");
  TEST_ASSERT_EQUAL_MESSAGE(true, canMove(GAME_SPEED + 1, 0), "Time passed +1");
  TEST_ASSERT_EQUAL_MESSAGE(true, canMove(GAME_SPEED + 100, 0), "Time passed +100");
}

void scheduleTester(int pin, int mode) {
  Serial.println("Scheduler executed on " + String(millis()));
}

void test_get_available_slot(void) {
  TEST_ASSERT_EQUAL_MESSAGE(0, getAvailableTaskSlot(), "Get first task slot (0)");
  schedule(1, scheduleTester, 1, millis() + 500);
  TEST_ASSERT_EQUAL_MESSAGE(1, getAvailableTaskSlot(), "Get next task slot (1)");
  schedule(2, scheduleTester, 2, millis() + 500);
  TEST_ASSERT_EQUAL_MESSAGE(2, getAvailableTaskSlot(), "Get next task slot (2)");
}

void test_complete_task(void) {
  /** Tasks were set on previous test **/
  completeTask(2);
  TEST_ASSERT_EQUAL_MESSAGE(true, getTasks()[2].done, "Get slot after complete task (2)");
  completeTask(1);
  TEST_ASSERT_EQUAL_MESSAGE(true, getTasks()[1].done, "Get slot after complete task (1)");
  completeTask(0);
  TEST_ASSERT_EQUAL_MESSAGE(true, getTasks()[0].done, "Get slot after complete task (0)");
}

void test_schedule(void) {
  unsigned long current = millis();
  TEST_ASSERT_EQUAL_MESSAGE(false, runSchedule(), "No tasks to run");

  schedule(4, scheduleTester, 4, 0);
  TEST_ASSERT_EQUAL_MESSAGE(true, runSchedule(), "Past task immediately executed");

  schedule(5, scheduleTester, 5, current + 300);
  TEST_ASSERT_EQUAL_MESSAGE(false, runSchedule(), "No tasks to run, added future task in 300ms");

  delay(300);
  TEST_ASSERT_EQUAL_MESSAGE(true, runSchedule(), "Task executed after 300ms");

  schedule(3, scheduleTester, 3, current + 400);
  delay(100);
  TEST_ASSERT_EQUAL_MESSAGE(true, runSchedule(), "Task executed after 400ms");

  schedule(4, scheduleTester, 4, current + 450);
  delay(50);
  TEST_ASSERT_EQUAL_MESSAGE(true, runSchedule(), "450 millis task");

  schedule(5, scheduleTester, 5, current + 470);
  delay(20);
  TEST_ASSERT_EQUAL_MESSAGE(true, runSchedule(), "470 millis task");

  schedule(6, scheduleTester, 6, current + 490);
  delay(20);
  TEST_ASSERT_EQUAL_MESSAGE(true, runSchedule(), "490 millis task");

  schedule(7, scheduleTester, 7, current + 600);

  while (millis() <= current + 600) {
    runSchedule();
  }

  TEST_ASSERT_EQUAL_MESSAGE(false, runSchedule(), "No tasks to run");
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_pulse);
    RUN_TEST(test_relay_pulse);
    UNITY_END();
    return;
    RUN_TEST(test_is_player);
    RUN_TEST(test_is_enemy);
    RUN_TEST(test_set_pos_value);
    RUN_TEST(test_out_of_bounds);
    RUN_TEST(test_time_up);
    RUN_TEST(test_can_move);
    RUN_TEST(test_get_available_slot);
    RUN_TEST(test_complete_task);
    RUN_TEST(test_schedule);
    UNITY_END();
}

void loop() {
}

#endif
