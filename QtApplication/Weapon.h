/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Weapon.h
Goal: Header file for the Weapon class.
Modifications:
*/

#ifndef WEAPON_H
#define WEAPON_H
#include <QElapsedTimer>

class Weapon {
private:
	int damage;
	float range;
	float fireRate;
    QElapsedTimer m_shootTimer;

public:
	Weapon(int dmg, float rng, float rate);
	~Weapon();
	void shoot();
	int getDamage();
	float getRange();
	float getFireRate();
    bool canShoot();
    void Shoot();
};

#endif
