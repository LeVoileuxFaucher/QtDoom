/*Projet S2 Hiver 2026
Code pour le joystick
Écrit par Félix Nolin-Aubertin*/

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

#define MIDDLE 511
#define DEAD_SPACE 15

#define DEAD_SPACE_MAX 1
#define MAX_VALUE 1023
#define MIN_VALUE 0

#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_SW 45

void joystick_setup();

bool isButtonPressed();

int readJoystick_x();

int readJoystick_y();

int8_t getJoystickMappedY();

int8_t getJoystickMappedX();

char getJoystickDirection();

#endif