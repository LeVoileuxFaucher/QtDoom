#include "Bouton.h"


static bool etatStable1 = false;
static bool etatPrecedent1 = false;
static bool derniereLecture1 = false;
static unsigned long dernierChangement1 = 0;

static bool etatStable2 = false;
static bool etatPrecedent2 = false;
static bool derniereLecture2 = false;
static unsigned long dernierChangement2 = 0;

static bool etatStable3 = false;
static bool etatPrecedent3 = false;
static bool derniereLecture3 = false;
static unsigned long dernierChangement3 = 0;

static bool etatStable4 = false;
static bool etatPrecedent4 = false;
static bool derniereLecture4 = false;
static unsigned long dernierChangement4 = 0;


void bouton_init(void)
{
    pinMode(BROCHE_BOUTON1, INPUT_PULLUP);
    pinMode(BROCHE_BOUTON2, INPUT_PULLUP);
    pinMode(BROCHE_BOUTON_ENCODER, INPUT_PULLUP);
    pinMode(BROCHE_BOUTON_JOYSTICK, INPUT_PULLUP);

    bool appuye = (digitalRead(BROCHE_BOUTON1) == LOW);
    etatStable1 = etatPrecedent1 = derniereLecture1 = appuye;
    dernierChangement1 = millis();

    appuye = (digitalRead(BROCHE_BOUTON2) == LOW);
    etatStable2 = etatPrecedent2 = derniereLecture2 = appuye;
    dernierChangement2 = millis();

    appuye = (digitalRead(BROCHE_BOUTON_ENCODER) == LOW);
    etatStable3 = etatPrecedent3 = derniereLecture3 = appuye;
    dernierChangement3 = millis();

    appuye = (digitalRead(BROCHE_BOUTON_JOYSTICK) == LOW);
    etatStable4 = etatPrecedent4 = derniereLecture4 = appuye;
    dernierChangement4 = millis();
}


void bouton_update(void)
{
    bool lecture;

    lecture = (digitalRead(BROCHE_BOUTON1) == LOW);
    if (lecture != derniereLecture1)
    {
        derniereLecture1 = lecture;
        dernierChangement1 = millis();
    }
    if ((millis() - dernierChangement1) >= DELAI_ANTI_REBOND)
    {
        etatPrecedent1 = etatStable1;
        etatStable1 = derniereLecture1;
    }


    lecture = (digitalRead(BROCHE_BOUTON2) == LOW);
    if (lecture != derniereLecture2)
    {
        derniereLecture2 = lecture;
        dernierChangement2 = millis();
    }
    if ((millis() - dernierChangement2) >= DELAI_ANTI_REBOND)
    {
        etatPrecedent2 = etatStable2;
        etatStable2 = derniereLecture2;
    }


    lecture = (digitalRead(BROCHE_BOUTON_ENCODER) == LOW);
    if (lecture != derniereLecture3)
    {
        derniereLecture3 = lecture;
        dernierChangement3 = millis();
    }
    if ((millis() - dernierChangement3) >= DELAI_ANTI_REBOND)
    {
        etatPrecedent3 = etatStable3;
        etatStable3 = derniereLecture3;
    }


    lecture = (digitalRead(BROCHE_BOUTON_JOYSTICK) == LOW);
    if (lecture != derniereLecture4)
    {
        derniereLecture4 = lecture;
        dernierChangement4 = millis();
    }
    if ((millis() - dernierChangement4) >= DELAI_ANTI_REBOND)
    {
        etatPrecedent4 = etatStable4;
        etatStable4 = derniereLecture4;
    }
}


bool bouton1_est_appuye(void) { return etatStable1; }
bool bouton1_vient_detre_appuye(void) { return (!etatPrecedent1 && etatStable1); }
bool bouton1_vient_detre_relache(void) { return (etatPrecedent1 && !etatStable1); }

bool bouton2_est_appuye(void) { return etatStable2; }
bool bouton2_vient_detre_appuye(void) { return (!etatPrecedent2 && etatStable2); }
bool bouton2_vient_detre_relache(void) { return (etatPrecedent2 && !etatStable2); }

bool bouton_encoder_est_appuye(void) { return etatStable3; }
bool bouton_encoder_vient_detre_appuye(void) { return (!etatPrecedent3 && etatStable3); }
bool bouton_encoder_vient_detre_relache(void) { return (etatPrecedent3 && !etatStable3); }

bool bouton_joystick_est_appuye(void) { return etatStable4; }
bool bouton_joystick_vient_detre_appuye(void) { return (!etatPrecedent4 && etatStable4); }
bool bouton_joystick_vient_detre_relache(void) { return (etatPrecedent4 && !etatStable4); }


int8_t boutons_vient_detre_appuye_octet(void)
{
    int8_t etat = 0;

    if (bouton1_vient_detre_appuye()) etat |= (1 << 0);
    if (bouton2_vient_detre_appuye()) etat |= (1 << 1);
    if (bouton_encoder_vient_detre_appuye()) etat |= (1 << 2);
    if (bouton_joystick_vient_detre_appuye()) etat |= (1 << 3);

    return etat;
}