#ifndef BOUTON_H
#define BOUTON_H

#include <Arduino.h>

#define BROCHE_BOUTON1 51
#define BROCHE_BOUTON2 53
#define BROCHE_BOUTON_ENCODER 18
#define BROCHE_BOUTON_JOYSTICK 22

#define DELAI_ANTI_REBOND 25 

void bouton_init(void);
void bouton_update(void);

bool bouton1_est_appuye(void);
bool bouton1_vient_detre_appuye(void);
bool bouton1_vient_detre_relache(void);

bool bouton2_est_appuye(void);
bool bouton2_vient_detre_appuye(void);
bool bouton2_vient_detre_relache(void);

bool bouton_encoder_est_appuye(void);
bool bouton_encoder_vient_detre_appuye(void);
bool bouton_encoder_vient_detre_relache(void);

bool bouton_joystick_est_appuye(void);
bool bouton_joystick_vient_detre_appuye(void);
bool bouton_joystick_vient_detre_relache(void);

int8_t boutons_vient_detre_appuye_octet(void);

#endif