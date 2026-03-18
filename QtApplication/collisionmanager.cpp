/*
Author: Donavan Sirois
Date: March 16, 2026
File name: collisionmanager.cpp
Description: Code for the collision handling of the game
Modifications:
*/

#include "collisionmanager.h"
#include<QDebug>

CollisionManager::CollisionManager()
{

}

void CollisionManager::handleCollisions(std::vector<Linedef>& broadedWalls, const std::vector<Vertex>& verteces, Actor* a)
{
    narrowingToCollide(broadedWalls, verteces, a);
}

void CollisionManager::narrowingToCollide(std::vector<Linedef>& broadedWalls, const std::vector<Vertex>& verteces, Actor* a)
{
    float radius = 2.0f;

    for (const Linedef wall: broadedWalls)
    {

        float dxPartition = verteces[wall.end].x - verteces[wall.start].x;
        float dyPartition = verteces[wall.end].y - verteces[wall.start].y;
        float dxPlayer = a->getPosition().x - verteces[wall.start].x;
        float dyPlayer = a->getPosition().y - verteces[wall.start].y;

        float wallLengthSq = dxPartition * dxPartition + dyPartition * dyPartition;

        float t = (dxPlayer * dxPartition + dyPlayer * dyPartition) / wallLengthSq;

        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;

        Vertex closestPoint = {verteces[wall.start].x + t * dxPartition,
                               verteces[wall.start].y + t * dyPartition};

        float dx = a->getPosition().x - closestPoint.x;
        float dy = a->getPosition().y - closestPoint.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < radius)
        {
            collide(closestPoint, a);
        }
    }
}

void CollisionManager::collide(Vertex closestPoint, Actor* a)
{
    float dx = a->getPosition().x - closestPoint.x;
    float dy = a->getPosition().y - closestPoint.y;

    float distanceToPoint = sqrt(dx * dx + dy * dy);

    if (distanceToPoint < 0.001f)
    {
        // Player is exactly on the wall - push slightly in arbitrary direction
        distanceToPoint = 0.001f;
        dx = 0.001f;
        dy = 0.0f;
    }

    float penetration = 2.0f - distanceToPoint; // radius - distance
    float normalX =  dx / distanceToPoint;
    float normalY =  dy / distanceToPoint;

    Vertex newPos = {a->getPosition().x + normalX * penetration, a->getPosition().y + normalY * penetration};
    a->setPosition(newPos);
}
