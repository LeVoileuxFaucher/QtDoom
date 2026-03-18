/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Weapon.cpp
Goal: Code file for the weapon class.
Modifications:
*/

#include "weapon.h"

Weapon::Weapon(int dmg, float rng, float rate, int maxAmmo, float reloadTime)
{
    damage        = dmg;
    range         = rng;
    fireRate      = rate;
    m_baseFireRate = rate;
    m_maxAmmo     = maxAmmo;
    m_baseMaxAmmo  = maxAmmo;
    m_currentAmmo = maxAmmo;
    m_reloadTime  = reloadTime;
    m_shootTimer.start();
    m_reloadTimer.start();
    m_powerUpCdTimer.start();
}

Weapon::~Weapon()
{
}

bool Weapon::canShoot()
{
    isReloading();
    if (m_isReloading)   return false;
    if (m_currentAmmo <= 0) return false;

    float cd = (1.0f / fireRate) * 10.0f;
    return m_shootTimer.elapsed() >= cd;
}

bool Weapon::cooldownReady()
{
    isReloading();
    if (m_isReloading) return false;
    float cd = (1.0f / fireRate) * 10.0f;
    return m_shootTimer.elapsed() >= cd;
}

void Weapon::shoot()
{
    m_currentAmmo--;
    updateBalles();
    m_shootTimer.restart();
}

void Weapon::reload()
{
    if (m_isReloading)        return;
    if (m_currentAmmo == m_maxAmmo) return;
    m_isReloading = true;
    m_reloadTimer.restart();
    m_shootTimer.restart();
    //qDebug("timer reload start");
    isReloading();
}

bool Weapon::isReloading()
{
    while (m_isReloading)
    {
        if (m_reloadTimer.elapsed() >= m_reloadTime * 1000.0f)
        {
            m_isReloading = false;
            m_currentAmmo = m_maxAmmo;
            //qDebug("fini reload");
            updateBalles();
            m_shootTimer.restart();
        }
    }
    return m_isReloading;
}

int Weapon::getDamage()
{
    return damage;
}

float Weapon::getRange()
{
    return range;
}

float Weapon::getFireRate()
{
    return fireRate;
}

void Weapon::restartShootTimer()
{
    m_shootTimer.restart();
}

void Weapon::powerUp()
{
    if (m_isPoweredUp) return;
    if (m_powerUpCdTimer.elapsed() < powerUpCd) return;

    qDebug("POWER UP activé");
    m_isPoweredUp  = true;
    m_maxAmmo      = m_baseMaxAmmo  * 4;
    fireRate       = m_baseFireRate * 2;
    m_currentAmmo  = m_maxAmmo;

    m_powerUpTimer.restart();
}

void Weapon::updatePowerUp()
{
    if (!m_isPoweredUp) return;

    if (m_powerUpTimer.elapsed() >= powerUpDuration)
    {
        qDebug("POWER UP terminé — cooldown démarré");
        m_isPoweredUp = false;
        m_maxAmmo     = m_baseMaxAmmo;
        fireRate      = m_baseFireRate;
        if (m_currentAmmo > m_maxAmmo)
            m_currentAmmo = m_maxAmmo;

        m_powerUpCdTimer.restart();
    }
}

bool Weapon::isPoweredUp() { return m_isPoweredUp; }

bool    Weapon::isEmpty()        { return m_currentAmmo <= 0; }
int     Weapon::getCurrentAmmo() { return m_currentAmmo;      }
int     Weapon::getMaxAmmo()     { return m_maxAmmo;          }

void Weapon::updateBalles()
{
    int balles=getCurrentAmmo();
    //qDebug("ammo left %d", balles);
    emit sigUpdateBalles(balles);
}

void Weapon::resetGameAmmo()
{
    m_currentAmmo = m_maxAmmo;
    updateBalles();
}
void    Weapon::setCurrentAmmo(int value) { m_currentAmmo = value; }
