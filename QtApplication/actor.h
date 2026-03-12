/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Player.h
Goal: Header file for the Player class managing player attributes and actions.
Modifications:
*/

#ifndef ACTOR_H
#define ACTOR_H

#include"geostructs.h"
#include "Weapon.h"

class Actor {
private:
    Vertex position;
    int health;
    bool isAlive;
    float angle;
    float EnemyRange = 15.0f;
    float EnemySpeed = 2.0f;
    float dx = 0;
    float dy = 0;

    Weapon* m_weapon = nullptr;

public:
    Actor();
    ~Actor();
    void move(float deltaX, float deltaY);
    void takeDamage(int amount);

    // Access to attributes
    int getHealth() {return health;}
    float getAngle() const {return angle;}
    Vertex getPosition() const {return position;}

    void setAngle(float newAngle);
    void rotate(float deltaAngle);
    void setPosition(float x, float y);

    //Enemy
    float distancePlayerEnemy(const Actor& E, const Actor& P);
    void moveEnemy(const Actor& P, float deltaTime);

    //Weapon
    void setWeapon(Weapon* w);
    Weapon* getWeapon() const;
    bool hasWeapon() const;
};

#endif
