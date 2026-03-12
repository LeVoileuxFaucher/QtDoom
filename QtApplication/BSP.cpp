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
            verteces.push_back(intersection);

            // Now, we just devide the segment with the two points and we push.
            Linedef segA = {segments[i].start, int(verteces.size()-1), 0, 10}; //segments[i].floorHeight, segments[i].ceilingHeight};
            Linedef segB = {int(verteces.size()-1), segments[i].end, 0, 10}; //segments[i].floorHeight, segments[i].ceilingHeight};

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
