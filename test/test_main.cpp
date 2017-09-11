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
    sendPulse(i);
    delay(100);
  }
}

void test_is_player(void) {
  setPlayerPosition(0,0, false);
  TEST_ASSERT_EQUAL_MESSAGE(true, isPlayer(0,0), "Is Player");
}

void test_is_enemy(void) {
  setEnemyPosition(0,0, false);
  TEST_ASSERT_EQUAL_MESSAGE(true, isEnemy(0,0), "Is Enemy");
}

void test_set_pos_value(void) {
  setPosValue(0,0,5);
  TEST_ASSERT_EQUAL_MESSAGE(5, getPosValue(0,0), "Set and Get 5 in pos 0,0");
}

void test_out_of_bounds(void) {
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(-1, 0), "Column in pos -1");
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(0, -1), "Row in pos -1");
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(boardMetadata.columns, 0), "Column at pos c+1");
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(0, boardMetadata.rows), "Row at pos r+1");
  setPosValue(0,0, testBoard.wall);
  TEST_ASSERT_EQUAL_MESSAGE(true, isOutOfBounds(0, 0), "Set a wall at pos 0,0");
}

void test_time_up(void) {
  TEST_ASSERT_EQUAL_MESSAGE(false, timeUp(100,0,200), "Half time passed");
  TEST_ASSERT_EQUAL_MESSAGE(true, timeUp(100,0,100), "Exact time passed");
  TEST_ASSERT_EQUAL_MESSAGE(true, timeUp(100,0,50), "Access time passed");
}

void test_can_move(void) {
  TEST_ASSERT_EQUAL_MESSAGE(false, canMove(GAME_SPEED - 200, 0), "200ms before");
  TEST_ASSERT_EQUAL_MESSAGE(false, canMove(GAME_SPEED - 100, 0), "100ms before");
  TEST_ASSERT_EQUAL_MESSAGE(true, canMove(GAME_SPEED, 0), "Exact time");
  TEST_ASSERT_EQUAL_MESSAGE(true, canMove(GAME_SPEED + 1, 0), "Time passed +1");
  TEST_ASSERT_EQUAL_MESSAGE(true, canMove(GAME_SPEED + 100, 0), "Time passed +100");
}

void scheduleTester(int pin, int mode) {
  Serial.println("Scheduler executed on " + String(millis()));
  Serial.println(String(pin) + " " + mode);
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
    // RUN_TEST(test_relay_pulse);
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
