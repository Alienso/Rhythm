//
// Created by Alienso on 17.5.2025.
//

#include "LevelLoader.h"
#include "reference/Global.h"
#include "entity/enemy/Nightmare.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <cstdio>

void LevelLoader::loadGeometryData(std::string& path, std::unordered_map<unsigned int, TilePositions>& sprites, size_t& nRows) {
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cout << "Could not open file: " << path << '\n';
        exit(1);
    }

    std::string line;
    size_t startIndex, endIndex;

    nRows = 20;
    float scale = 2.0f/(float)nRows;
    std::vector<std::vector<TileInstance>> terrainTiles;

    for(int i = 0; std::getline(inputFile, line); i++) {
        startIndex = 0;
        terrainTiles.emplace_back();
        for(int j=0;;j++) {
            endIndex = line.find(';', startIndex);
            if (endIndex == startIndex) {
                startIndex = endIndex + 1;

                Tile* tile = Tiles::BLANK;

                glm::vec2 position = {j, i};

                position.x += tile->offset.x;
                position.y -= tile->offset.y;
                position *= scale;
                position.x -= Configuration::aspectRatio / 2.0f;
                position.x -= 1 - scale / 2;
                position.y -= 1 - scale / 2;
                position.y *= -1;

                terrainTiles[i].emplace_back(tile, position);
                continue;
            }

            if (endIndex == std::string::npos) break;
            unsigned int id = std::stoi(line.substr(startIndex, endIndex - startIndex));
            startIndex = endIndex + 1;

            Tile* tile = Global::tileManager->getAsset(id);
            if (sprites.find(id) == sprites.end())
                sprites[id] = TilePositions{tile};

            glm::vec2 position = {j, i};

            position.x += tile->offset.x;
            position.y -= tile->offset.y;
            position *= scale;
            position.x -= Configuration::aspectRatio / 2.0f;
            position.x -= 1 - scale / 2;
            position.y -= 1 - scale / 2;
            position.y *= -1;

            sprites[id].positions.emplace_back(position.x, position.y);
            terrainTiles[i].emplace_back(tile, position);
        }
        //nRows++;
    }

    Global::physicsEngine->registerTerrainTiles(terrainTiles);
}

void LevelLoader::loadRooms(const char* basePath, std::vector<std::string>& roomPaths , std::vector<Room> &rooms) {

    for (std::string& path : roomPaths) {
        std::ifstream inputFile(std::string(basePath) + path);
        if (!inputFile.is_open()) {
            std::cout << "Could not open file: " << path << '\n';
            exit(1);
        }

        nlohmann::json roomJson = nlohmann::json::parse(inputFile);
        Room room;

        for (const auto& weaveJson : roomJson){
            float spawnDelay = weaveJson["spawnDelay"].get<float>();
            int minEnemiesAliveForNext = weaveJson["minEnemiesAliveForNext"].get<int>();
            std::vector<Spawn> spawns;

            for (const auto& spawnJson : weaveJson["spawns"]) {
                float posX = spawnJson["posX"].get<float>();
                float posY = spawnJson["posY"].get<float>();
                int entityId = spawnJson["entityId"].get<int>();
                float waveSpawnDelay = spawnJson["spawnDelay"].get<float>();

                EntityLiving* entity = new Nightmare(); // TODO

                spawns.emplace_back(glm::vec2(posX, posY), entity, waveSpawnDelay);
            }

            room.weaves.emplace_back(spawnDelay, minEnemiesAliveForNext, spawns);
        }
        rooms.push_back(room);
    }
}
