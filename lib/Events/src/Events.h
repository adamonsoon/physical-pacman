#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define PACMAN_ID   10
#define MONSTER1_ID  20
#define MONSTER2_ID 30

#define PAYLOAD_SIZE 2

#define STATE_IDLE 1
#define STATE_OFF  2
#define STATE_PACMAN_DEFAULT       3
#define STATE_MONSTER_VULNERABLE   4
#define STATE_MONSTER_UNVULNERABLE 8
#define STATE_MONSTER_INVISIBLE    9
#define STATE_MONSTER_EATING      10
#define STATE_MONSTER_WEAK        11
#define STATE_PACMAN_EATING        5
#define STATE_PACMAN_EATEN         7

extern void setupMirf();
extern void dispatchEvent(byte event, byte identifier);

#endif
