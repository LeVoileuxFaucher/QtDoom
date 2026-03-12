/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: Player.cpp
Goal: Code for the Player class managing player attributes and actions.
Modifications:
*/

#include "actor.h"
#include <cmath>

Actor::Actor()
{
    position = {0, 0};
    angle = 0.0f;
    health = 15;
    isAlive = true;
}

Actor::~Actor()
{

}

void Actor::move(float deltaX, float deltaY)
{
    position.x += deltaX;
    position.y += deltaY;
}

void Actor::takeDamage(int amount)
{
    health -= amount;
    if (health < 0)
    {
        health = 0;
        isAlive = false;
    }
}

void Actor::setAngle(float a)
{
    angle = a;
}

void Actor::rotate(float a)
{
    angle += a;
}

void Actor::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

//Enemy

float Actor::distancePlayerEnemy(const Actor& E,const Actor& P)
{
    dx= P.getPosition().x-E.getPosition().x;
    dy = P.getPosition().y-E.getPosition().y;

    return std::sqrt(dx*dx + dy*dy);
}

void Actor::moveEnemy(const Actor& Player, float deltaTime)
{
    if(canMove)
    {
        float distX = Player.getPosition().x - position.x;
        float distY = Player.getPosition().y - position.y;
        float distance = std::sqrt(distX * distX + distY * distY);


        angle = std::atan2(distY, distX);


        if (distance < EnemyRange && distance > 0.01f)
        {
            float nx = distX / distance;
            float ny = distY / distance;
            position.x += nx * EnemySpeed * deltaTime;
            position.y += ny * EnemySpeed * deltaTime;
        }
    }

}

void Actor::setWeapon(Weapon *w)
{
    m_weapon = w;
}

Weapon* Actor::getWeapon() const
{
    return m_weapon;
}

bool Actor::hasWeapon() const
{
    if(m_weapon!=nullptr)
    {
        return true;
    }
    return false;
}
void Actor::setMovement(bool movement)
{
    canMove = movement;
}

