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
#include <QObject>

#include"actor.h"
#include"geostructs.h"
#include"bsp.h"
#include "Weapon.h"
#include"mapreader.h"

class GameManager: public QObject
{
    Q_OBJECT
public:
    GameManager();
    Actor* getPlayer();
    Actor* getEnemy();
    BSP* getBSP();
    void loadMap(const std::string& filename);
    void update(float deltaTime, std::vector<Linedef> renderedWalls);
    bool inRadius(Actor *p, Actor *e);
    bool shoot(QPoint mousePos, QSize screenSize);

    const std::vector<Vertex>& getVerteces() const {return verteces;};
    const std::vector<Linedef>& getLinedefs() const {return linedefs;};
    const std::vector<Sector>& getSectors() const {return sectors;};

    void updateVie();
    Weapon* getWeapon();
    void restartGame();

private:
    Actor *p;
    Actor *e;
    std::vector<Actor*> creatures;
    BSP* bsp = nullptr;
    Weapon* m_playerWeapon = nullptr;
    MapReader* map;

    // Map data
    std::vector<Vertex> verteces;
    std::vector<Linedef> linedefs;
    std::vector<Sector> sectors;

    QElapsedTimer m_enemyAttackTimer;
    float m_attackCooldown = 1000.0f;
    bool m_inContact = false;

signals:
    void sigUpdateVie(int value);
    void sigUpdateBalles(int value);
    void playerDead();
};

#endif // GAMEMANAGER_H
