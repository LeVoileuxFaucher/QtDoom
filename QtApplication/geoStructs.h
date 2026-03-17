/*
Author: Donavan Sirois
Date: Febuary 13, 2026
File name: geoStructs.h
Goal: Header file for defining geomtry structures used for the map and the renderer.
Modifications:
*/

#ifndef GEOSTRUCTS_H
#define GEOSTRUCTS_H

#include<vector>

struct Vertex // Think of it as a 2D point
{
    float x, y;
};

struct Linedef // Think of it as a segment or a line
{
    int start; // Index to the vertex array
    int end; // Index to the vertex array
    int sideFront; // Sector index (front of the wall) (-1 if none)
    int sideBack; // Sector index (back of the wall) (-1 if none)
    bool twoSided;
};

struct Sidedef // Think of it as one side of the segment or the line, probably not needed because we don't render different textures
{
    int sectorRef;
};

struct Sector // Think of it as a polygon
{
    std::vector<int> linedefs;
    float floorHeight;
    float ceilingHeight;
};

#endif
