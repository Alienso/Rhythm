//
// Created by Alienso on 17.5.2025.
//

#ifndef RHYTHM_LEVELLOADER_H
#define RHYTHM_LEVELLOADER_H

#include "Tile.h"
#include "Room.h"

#include <unordered_map>

class LevelLoader {
public:
    static void loadGeometryData(std::string& path, std::unordered_map<unsigned int, TilePositions>& sprites, size_t& nRows);
    static void loadRooms(const char* basePath, std::vector<std::string>& roomPaths, std::vector<Room>& rooms);

};


#endif //RHYTHM_LEVELLOADER_H
