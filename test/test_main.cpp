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

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_relay_pulse);
    RUN_TEST(test_is_player);
    RUN_TEST(test_is_enemy);
    RUN_TEST(test_set_pos_value);
    RUN_TEST(test_out_of_bounds);
    UNITY_END();
}

void loop() {
}

#endif
