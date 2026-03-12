/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Engine.h
Description: Header file for the game engine handling all events.
Modifications:
*/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<string>
#include <QApplication>
#include <QProcess>
#include <QElapsedTimer>

#include"actor.h"
#include"geostructs.h"
#include"bsp.h"
#include "Weapon.h"

class GameManager
{
public:
    GameManager();
    Actor* getPlayer();
    Actor* getEnemy();
    BSP* getBSP();
    void loadMap(const std::string& filename);
    void update(float deltaTime, std::vector<Linedef> renderedWalls);
    bool inRadius(Actor *p, Actor *e);
    bool shoot(QPoint mousePos, QSize screenSize);
private:
    Actor *p;
    Actor *e;
    std::vector<Actor*> creatures;
    std::vector<Linedef> walls;
    BSP* bsp;
    Weapon* m_playerWeapon = nullptr;

    QElapsedTimer m_enemyAttackTimer;
    float m_attackCooldown = 1000.0f;
    bool m_inContact = false;
};

#endif // GAMEMANAGER_H
