#include "Accelerometre.h"

float xBase = 0;
float yBase = 0;
float zBase = 0;

void SetupAccelerometre()
{
    pinMode(PIN_X, INPUT);
    pinMode(PIN_Y, INPUT);
    pinMode(PIN_Z, INPUT);
}

void CalibrerAccelerometre(int nbMesures)
{
    float sumX = 0, sumY = 0, sumZ = 0;
    for (int i = 0; i < nbMesures; i++)
    {
        sumX += analogRead(PIN_X) * (3.3 / 1023.0);
        sumY += analogRead(PIN_Y) * (3.3 / 1023.0);
        sumZ += analogRead(PIN_Z) * (3.3 / 1023.0);
        delay(5);
    }
    xBase = sumX / nbMesures;
    yBase = sumY / nbMesures;
    zBase = sumZ / nbMesures;
}

void lireAxes(float &x, float &y, float &z)
{
    x = analogRead(PIN_X) * (3.3 / 1023.0) - xBase;
    y = analogRead(PIN_Y) * (3.3 / 1023.0) - yBase;
    z = analogRead(PIN_Z) * (3.3 / 1023.0) - zBase;
}

int detecterMouvement(float dx, float dy, float dz)
{
    float deltaX = fabs(dx) - threshold;
    float deltaY = fabs(dy) - threshold;
    float deltaZ = fabs(dz) - threshold;

    if (deltaX <= 0 && deltaY <= 0 && deltaZ <= 0)
        return HAUT;

    if (deltaX >= deltaY && deltaX >= deltaZ)
        return (dx > 0) ? GAUCHE : DROITE;
    else if (deltaY >= deltaX && deltaY >= deltaZ)
        return (dy < 0) ? AVANT : ARRIERE;
    else
        return BAS;
}

void getCursorPosition(int &xScreen, int &yScreen, int width, int height)
{
    float x, y, z;
    lireAxes(x, y, z);

    const float maxTilt = 0.3f;
    const float gain    = 2.0f;

    x = constrain(x * gain, -maxTilt, maxTilt);
    y = constrain(-y * gain, -maxTilt, maxTilt);

  
    xScreen = (int)((-x + maxTilt) / (2.0f * maxTilt) * 255.0f);
    yScreen = (int)(( y + maxTilt) / (2.0f * maxTilt) * 255.0f);

    xScreen = constrain(xScreen, 0, 255);
    yScreen = constrain(yScreen, 0, 255);
}