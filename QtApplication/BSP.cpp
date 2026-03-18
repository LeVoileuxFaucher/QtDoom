/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: BSP.cpp
Description: Code for the Binary Space Partitioning tree implementation.
Modifications:
*/

#include "bsp.h"

BSP::BSP()
{
    root = nullptr;
}

Node* BSP::Builder(std::vector<Linedef> segments, std::vector<Vertex>& verteces)
{
    // Safety verifications
    if (segments.empty()) return nullptr;
    if (segments.size() == 1)
    {
        Node* node = new Node();
        node->partition = segments[0];
        node->front = nullptr;
        node->back = nullptr;
        return node;
    }

    // Defining the partition (later will be called optimally, right now we only use the first segment)
    Node* node = new Node();
    node->partition = segments[0];

    std::vector<Linedef> frontLines;
    std::vector<Linedef> backLines;

    for (int i = 1; i < segments.size(); i++) // Starting at 1, since we use 0 as the partition
    {

        // We make the cross product to evaluate the position of a line compared to the partition
        float deltaXSegmentEnd = verteces[segments[i].end].x - verteces[node->partition.start].x;
        float deltaYSegmentEnd = verteces[segments[i].end].y - verteces[node->partition.start].y;
        float deltaXSegmentStart = verteces[segments[i].start].x - verteces[node->partition.start].x;
        float deltaYSegmentStart = verteces[segments[i].start].y - verteces[node->partition.start].y;
        float deltaXPartition = verteces[node->partition.end].x - verteces[node->partition.start].x;
        float deltaYPartition = verteces[node->partition.end].y - verteces[node->partition.start].y;

        float crossProductEnd = (deltaXSegmentEnd * deltaYPartition) - (deltaYSegmentEnd * deltaXPartition);
        float crossProductStart = (deltaXSegmentStart * deltaYPartition) - (deltaYSegmentStart * deltaXPartition);

        if (crossProductEnd > 0 && crossProductStart > 0)
        { // is in front (arbitrarilly), i.e. all point of the line are in front of the partition line
            frontLines.push_back(segments[i]);
        }
        else if (crossProductEnd < 0 && crossProductStart < 0)
        { // is at the back (arbitrarilly), i.e. all the points of the line are at the back of the partition line
            backLines.push_back(segments[i]);
        }
        else // is split by the segment
        {
            // Let's create a new point to divide the segment into a front one and a back one
            Vertex intersection;

            float dxSeg = verteces[segments[i].end].x - verteces[segments[i].start].x;
            float dySeg = verteces[segments[i].end].y - verteces[segments[i].start].y;
            float dxPar = verteces[node->partition.end].x - verteces[node->partition.start].x;
            float dyPar = verteces[node->partition.end].y - verteces[node->partition.start].y;

            if (dxSeg == 0) // vertical segment case
            {
                intersection.x = verteces[segments[i].start].x;
                if (dxPar != 0) intersection.y = verteces[node->partition.start].y + (intersection.x - verteces[node->partition.start].x) * (dyPar / dxPar); // vertical partition case
                else intersection.y = verteces[segments[i].start].y;
            }
            else if (dxPar == 0) // vertical partition case
            {
                intersection.x = verteces[node->partition.start].x;
                intersection.y = verteces[segments[i].start].y + (intersection.x - verteces[segments[i].start].x) * dySeg / dxSeg;
            }
            else
            {
                float slopeSeg = dySeg/dxSeg;
                float slopePar = dyPar/dxPar;

                float bSeg = verteces[segments[i].end].y - (slopeSeg*verteces[segments[i].end].x);
                float bPar = verteces[node->partition.end].y - (slopePar*verteces[node->partition.end].x);

                // Now, we find the intersection point.
                //This could be done from the biginning, but for readability, we created new variables.
                intersection.x = (bSeg - bPar) / (slopePar - slopeSeg);
                intersection.y = (slopeSeg*intersection.x) + bSeg;
            }
            /*
            auto found = std::find_if(verteces.begin(), verteces.end(),
                                      [&](const Vertex& v) {
                                          return fabs(v.x - intersection.x) < 0.001f &&
                                                 fabs(v.y - intersection.y) < 0.001f;
                                      });

            int vertexIndex = 0;
            qDebug() << std::distance(verteces.begin(), found);;
            if (found != verteces.end()) {
                vertexIndex = std::distance(verteces.begin(), found);
            } else {
                verteces.push_back(intersection);
                vertexIndex = verteces.size() - 1;
            }
            */

            verteces.push_back(intersection);
            int vertexIndex = verteces.size() - 1;

            // Now, we just devide the segment with the two points and we push.
            Linedef segA = {segments[i].start, vertexIndex, segments[i].sideFront, segments[i].sideBack, segments[i].twoSided};
            Linedef segB = {vertexIndex, segments[i].end, segments[i].sideFront, segments[i].sideBack, segments[i].twoSided};

            if (crossProductStart > 0)
            {
                frontLines.push_back(segA);
                backLines.push_back(segB);
            }
            else
            {
                backLines.push_back(segA);
                frontLines.push_back(segB);
            }
        }
    }
    node->front = Builder(frontLines, verteces);
    node->back = Builder(backLines, verteces);
    return node;
}

// These functions order the walls. THEY DO NOT ACCOUNT FOR VIEW CULLING YET! THIS MEANS EVERY WALL GETS RENDERED!
void BSP::traverse(const Vertex& playerPosition, std::vector<Linedef>& renderedWalls, const std::vector<Vertex>& verteces)
{
    renderedWalls.clear();
    traverseNode(root, playerPosition, renderedWalls, verteces);
}

void BSP::traverseNode(Node* node, const Vertex& playerPosition, std::vector<Linedef>& walls, const std::vector<Vertex>& verteces)
{
    if (!node) return;

    float dxPartition = verteces[node->partition.end].x - verteces[node->partition.start].x;
    float dyPartition = verteces[node->partition.end].y - verteces[node->partition.start].y;
    float dxPlayer = playerPosition.x - verteces[node->partition.start].x;
    float dyPlayer = playerPosition.y - verteces[node->partition.start].y;

    float cross = dxPartition * dyPlayer - dyPartition * dxPlayer;

    if (cross < 0)
    {
        traverseNode(node->back, playerPosition, walls, verteces);
        walls.push_back(node->partition);
        traverseNode(node->front, playerPosition, walls, verteces);
    }
    else
    {
        traverseNode(node->front, playerPosition, walls, verteces);
        walls.push_back(node->partition);
        traverseNode(node->back, playerPosition, walls, verteces);
    }
}

void BSP::build(const std::vector<Linedef>& segments, std::vector<Vertex>& verteces)
{
    delete root;
    root = Builder(segments, verteces);
}

void BSP::actorToWallBroading(const Vertex& actorPosition, std::vector<Linedef>& broadedWalls, const std::vector<Vertex>& verteces)
{
    broadedWalls.clear();
    broadWall(root, actorPosition, broadedWalls, verteces);
}

void BSP::broadWall(Node* node, const Vertex& playerPosition, std::vector<Linedef>& broadedWalls, const std::vector<Vertex>& verteces)
{
    if (!node) return;

    float radius = 2.0f;

    float dxPartition = verteces[node->partition.end].x - verteces[node->partition.start].x;
    float dyPartition = verteces[node->partition.end].y - verteces[node->partition.start].y;
    float dxPlayer = playerPosition.x - verteces[node->partition.start].x;
    float dyPlayer = playerPosition.y - verteces[node->partition.start].y;

    float cross = dxPartition * dyPlayer - dyPartition * dxPlayer;

    // Here, we decide to not only broad the wall, but to do some volume culling.
    // We check if the player is at a reasonable distance of the wall. If he is, we add it to the valid walls.
    // This is called bounding volume hierarchy (BVH).
    // It is furthermore usefull with BSP, as it eliminates having to pass through the children of a given node.

    float wallLength = sqrt(dxPartition * dxPartition + dyPartition * dyPartition);
    float distance = cross / wallLength;

    broadedWalls.push_back(node->partition);

    if (distance > radius)
    {
        broadWall(node->front, playerPosition, broadedWalls, verteces);
    }
    else if (distance < -radius)
    {
        broadWall(node->back, playerPosition, broadedWalls, verteces);
    }
    else
    {
        broadWall(node->front, playerPosition, broadedWalls, verteces);
        broadWall(node->back, playerPosition, broadedWalls, verteces);
    }
}

float crossProduct(Vertex v, Linedef l)
{
    return 0.1f;
}

float crossProduct(Linedef l1, Linedef l2)
{
    return 0.1f;
}
