//
// Created by Alienso on 17.5.2025.
//

#ifndef RHYTHM_LEVELLOADER_H
#define RHYTHM_LEVELLOADER_H

#include "Tile.h"
#include "Room.h"

#include <unordered_map>

struct LevelGeometryData {
    std::unordered_map<unsigned int, TilePositions> backgroundSpritePositions;
    std::unordered_map<unsigned int, TilePositions> foregroundSpritePositions;
    size_t nRows;
};

class LevelLoader {
public:
    static LevelGeometryData loadGeometryData(std::string& path);
    static void loadRooms(const char* basePath, std::vector<std::string>& roomPaths, std::vector<Room>& rooms);

};


#endif //RHYTHM_LEVELLOADER_H
