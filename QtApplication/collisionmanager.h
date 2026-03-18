/*
Author: Donavan Sirois
Date: March 16, 2026
File name: collisionmanager.h
Description: Class for the collision handling of the game
Modifications:
*/

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "geostructs.h"
#include "actor.h"

class CollisionManager
{
public:
    CollisionManager();
    void handleCollisions(std::vector<Linedef>& broadedWalls, const std::vector<Vertex>& verteces, Actor* a);
    void narrowingToCollide(std::vector<Linedef>& broadedWalls, const std::vector<Vertex>& verteces, Actor* a);
    void collide(Vertex closestPoint, Actor* a);


    // We conpute the new position of the objects.
};

#endif
