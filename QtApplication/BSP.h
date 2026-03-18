/*
Author name: Donavan Sirois
Date: Febuary 1, 2026
File name: BSP.h
Description: Header file for the Binary Space Partitioning tree implementation.
Modifications:
*/

#ifndef BSP_H
#define BSP_H

#include<QDebug>

#include"geostructs.h"

struct Node
{
    Linedef partition;
    Node* front;
    Node* back;
};

class BSP
{
public:
    BSP();
    Node* Builder(std::vector<Linedef> segments, std::vector<Vertex>& verteces);
    void traverse(const Vertex& playerPosition, std::vector<Linedef>& renderedWalls, const std::vector<Vertex>& verteces);
    void traverseNode(Node* node, const Vertex& playerPos, std::vector<Linedef>& walls, const std::vector<Vertex>& verteces);
    void build(const std::vector<Linedef>& segments, std::vector<Vertex>& verteces);

    void broadWall(Node* node, const Vertex& playerPosition, std::vector<Linedef>& broadedWalls, const std::vector<Vertex>& verteces);
    void actorToWallBroading(const Vertex& actorPosition, std::vector<Linedef>& broadedWalls, const std::vector<Vertex>& verteces);
private:
    Node* root;
};

#endif
