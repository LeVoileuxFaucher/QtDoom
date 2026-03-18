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
#include <QObject>

class Weapon: public QObject{
    Q_OBJECT
private:
    int damage;
    float range;
    float fireRate;
    float m_baseFireRate;
    int   m_baseMaxAmmo;

    QElapsedTimer m_shootTimer;
    QElapsedTimer m_reloadTimer;
    QElapsedTimer m_powerUpTimer;
    QElapsedTimer m_powerUpCdTimer;

    float powerUpDuration = 10000.0f;
    float powerUpCd       = 5000.0f;

    int   m_maxAmmo;
    int   m_currentAmmo;
    float m_reloadTime;
    bool  m_isReloading  = false;
    bool  m_isPoweredUp  = false;

public:
    Weapon(int dmg, float rng, float rate, int maxAmmo, float reloadTime);
    ~Weapon();
    void shoot();
    int   getDamage();
    float getRange();
    float getFireRate();
    int   getCurrentAmmo();
    int   getMaxAmmo();
    bool  canShoot();
    bool  cooldownReady();
    void  reload();
    bool  isReloading();
    bool  isEmpty();
    void  restartShootTimer();
    void  powerUp();
    void  updatePowerUp();
    bool  isPoweredUp();
    void updateBalles();
    void resetGameAmmo();
    void setCurrentAmmo(int value);

signals:
    void sigUpdateBalles(int value);
};

#endif
