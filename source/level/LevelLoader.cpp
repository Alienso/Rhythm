//
// Created by Alienso on 17.5.2025.
//

#include "LevelLoader.h"
#include "reference/Global.h"
#include "entity/enemy/Nightmare.h"

#include <fstream>
#include <cstdio>

void LevelLoader::loadGeometryData(const char * path, std::unordered_map<unsigned int, TilePositions>& sprites, size_t& nRows) {
    std::ifstream inputFile(std::string(path) + ".geo");
    std::string line;

    size_t startIndex, endIndex;

    for(int i=0; std::getline(inputFile, line); i++){
        startIndex = 0;
        for(int j=0;;j++) {
            endIndex = line.find(';', startIndex);
            if (endIndex == startIndex) {
                startIndex = endIndex + 1;
                continue;
            }

            if (endIndex == std::string::npos) break;
            unsigned int id = std::stoi(line.substr(startIndex, endIndex - startIndex));
            startIndex = endIndex + 1;

            Tile* tile = Global::tileManager->getAsset(id);
            if (sprites.find(id) == sprites.end())
                sprites[id] = TilePositions{tile};
            sprites[id].positions.emplace_back(j, i);
        }
        nRows++;
    }
}

void LevelLoader::loadRooms(const char *path, std::vector<Room> &rooms) {
    std::ifstream inputFile(std::string(path) + ".room");
    std::string line;

    int bracketCounter =  0;
    //Skip first line which is header
    std::getline(inputFile, line);

    Room room;

    float startDelay;
    int minEnemiesAliveForNext;
    std::vector<Spawn> spawns{};
    spawns.reserve(64);

    while(std::getline(inputFile, line)){

        if (line.empty())
            continue;

        if (line[0] == '-'){
            rooms.push_back(room);
            room = {};
            continue;
        }

        if (isspace(line[0])){
            do{
                if (line.empty())
                    continue;
                if (line[0] == '}')
                    break;

                float posX, posY, spawnDelay;
                int entityId;
                int read = sscanf(line.c_str(), "    { %f, %f, %d, %f },", &posX, &posY, &entityId, &spawnDelay);
                assert(read == 4);
                spawns.emplace_back(glm::vec2{posX, posY}, new Nightmare(), spawnDelay); //TODO entityId?
            }while(std::getline(inputFile, line));
        }

        if (line[0] == '{') {
            assert(bracketCounter == 0);
            bracketCounter++;
            int read = sscanf(line.c_str(), "{ %f, %d", &startDelay, &minEnemiesAliveForNext);
            assert(read == 2);
            continue;
        }
        if (line[0] == '}') {
            assert(bracketCounter == 1);
            bracketCounter--;

            //Do some logic
            room.weaves.emplace_back(startDelay, minEnemiesAliveForNext, spawns);
            spawns.clear();
            continue;
        }
        assert(false);
    }

    rooms.push_back(room);
}
