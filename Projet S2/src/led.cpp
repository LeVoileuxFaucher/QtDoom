#include "led.h"

void SetupLed()
{
    pinMode(PIN_A, OUTPUT);
    pinMode(PIN_B, OUTPUT);
    pinMode(PIN_C, OUTPUT);
    pinMode(PIN_D4, OUTPUT);
    pinMode(PIN_D5, OUTPUT);
    pinMode(PIN_Vert, OUTPUT);
    pinMode(PIN_Rouge, OUTPUT);
    pinMode(PIN_ENABLE, OUTPUT);
}

void UpdateLed(uint16_t choix)
{
    static uint8_t muxIndex = 0;
    static unsigned long previousMillis = 0;
    const uint8_t interval = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis < interval)
        return;
    previousMillis = currentMillis;

    // Désactivation générale avant mise à jour
    digitalWrite(PIN_ENABLE, LOW);
    digitalWrite(PIN_D4, HIGH);
    digitalWrite(PIN_D5, HIGH);
    digitalWrite(PIN_Vert, HIGH);
    digitalWrite(PIN_Rouge, HIGH);

    uint8_t count = 0;

    // Mise à jour de la séquence pour les LEDs 1 à 10 (muxIndex 0 à 9)
    while (count < 10)  // uniquement 0..9
    {
        if (bitRead(choix, muxIndex))
        {
            if (muxIndex < 8) // Mux pour LEDs 1-8
            {
                digitalWrite(PIN_A, (muxIndex >> 0) & 0x01);
                digitalWrite(PIN_B, (muxIndex >> 1) & 0x01);
                digitalWrite(PIN_C, (muxIndex >> 2) & 0x01);
                digitalWrite(PIN_ENABLE, HIGH);
            }
            else // LEDs 9 et 10
            {
                digitalWrite(PIN_ENABLE, LOW);

                switch (muxIndex)
                {
                    case 8:
                        digitalWrite(PIN_D5, LOW);
                        break;
                    case 9:
                        digitalWrite(PIN_D4, LOW);
                        break;
                }
            }

            muxIndex++;
            if (muxIndex >= 10)
                muxIndex = 0;
            break;
        }

        muxIndex++;
        if (muxIndex >= 10)
            muxIndex = 0;
        count++;
    }

    // LEDs 11 et 12 (bits 10 et 11) activées/désactivées selon le bit
    digitalWrite(PIN_Rouge, bitRead(choix, 10) ? LOW : HIGH);
    digitalWrite(PIN_Vert, bitRead(choix, 11) ? LOW : HIGH);
}

uint16_t ShiftRight(uint16_t value)
{
    uint16_t msb = value   & 0b110000000000;
    uint16_t lower = value & 0b001111111111;

    lower = lower >> 1;

    return msb | lower;
}

uint16_t ShiftLeft(uint16_t value)
{
    uint16_t msb = value   & 0b110000000000;
    uint16_t lower = value & 0b001111111111;

    lower = lower << 1;

    return msb | lower;
}

uint16_t CalculeBargraph(int valeurAnalogique)
{
    const int minVal = 500;
    const int maxVal = 1020;
    const uint16_t mask = 0b111111111111;

    if (valeurAnalogique < minVal)
        valeurAnalogique = minVal;
    if (valeurAnalogique > maxVal)
        valeurAnalogique = maxVal;

    int bitsToSet = map(valeurAnalogique, minVal, maxVal, 0, 12);

    uint16_t result = 0;

    for (int i = 0; i < 12; i++)
    {
        if (bitRead(mask, i))
        {
            if (bitsToSet > 0)
            {
                bitSet(result, i);
                bitsToSet--;
            }
        }
    }

    return result;
}

void EteindreLeds()
{
    digitalWrite(47, LOW);
}