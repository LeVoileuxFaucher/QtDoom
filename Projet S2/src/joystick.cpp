/*Projet S2 Hiver 2026
Code pour le joystick
Écrit par Félix Nolin-Aubertin*/

#include "joystick.h"

void joystick_setup()
{
    pinMode(JOYSTICK_X, INPUT);
    pinMode(JOYSTICK_Y, INPUT);
    pinMode(JOYSTICK_SW, INPUT);
}

bool isButtonPressed()
{
    return (digitalRead(JOYSTICK_SW));
}

int readJoystick_x()
{
    int read = analogRead(JOYSTICK_X);

    
    if (read < MIDDLE + DEAD_SPACE && read > MIDDLE - DEAD_SPACE)
    {
        read = MIDDLE;
    }

    
    if (read < MIN_VALUE + DEAD_SPACE_MAX)
    {
        read = MIN_VALUE;
    }

    
    if (read > MAX_VALUE - DEAD_SPACE_MAX)
    {
        read = MAX_VALUE;
    }

    return read;
}

int readJoystick_y()
{
    int read = analogRead(JOYSTICK_Y);

   
    if (read < MIDDLE + DEAD_SPACE && read > MIDDLE - DEAD_SPACE)
    {
        read = MIDDLE;
    }

    
    if (read < MIN_VALUE + DEAD_SPACE_MAX)
    {
        read = MIN_VALUE;
    }

    
    if (read > MAX_VALUE - DEAD_SPACE_MAX)
    {
        read = MAX_VALUE;
    }

    return read;
}
char getJoystickDirection()
{
    int x = readJoystick_x();
    int y = readJoystick_y();

    if (x == MIDDLE && y == MIDDLE)
    {
        return 'C'; // Centre
    }

    if (y == MAX_VALUE)
    {
        return 'F'; // Avant
    }

    if (y == MIN_VALUE)
    {
        return 'B'; // Arrière
    }

    if (x == MIN_VALUE)
    {
        return 'L'; // Gauche
    }

    if (x == MAX_VALUE)
    {
        return 'R'; // Droite
    }

    return 'C';
}

int8_t getJoystickMappedX()
{
    int val = readJoystick_x();
    val = constrain(val, MIN_VALUE, MAX_VALUE);
    return map(val, MIN_VALUE, MAX_VALUE, 0, 255);
}

int8_t getJoystickMappedY()
{
    int val = readJoystick_y();
    val = constrain(val, MIN_VALUE, MAX_VALUE);
    return map(val, MIN_VALUE, MAX_VALUE, 0, 255);
}