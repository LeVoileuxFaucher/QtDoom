/*
Author: Donavan Sirois
Date: March 4, 2026
File name: mapreader.h
Description: Header file of the map loader called upon starting the game.
Modifications:
*/

#ifndef MAPREADER_H
#define MAPREADER_H

#include<string>
#include <fstream>
#include <sstream>
#include"geostructs.h"

class MapReader
{
public:
    MapReader();
    bool load(std::string mapName);

    const std::vector<Vertex>& getVerteces() const {return verteces;};
    const std::vector<Linedef>& getLinedefs() const {return linedefs;};
    const std::vector<Sector>& getSectors() const {return sectors;};
private:
    std::vector<Vertex> verteces;
    std::vector<Linedef> linedefs;
    std::vector<Sector> sectors;
};

#endif // MAPREADER_H
