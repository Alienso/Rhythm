//
// Created by Alienso on 17.5.2025.
//

#include "LevelLoader.h"
#include "reference/Global.h"
#include "entity/enemy/Nightmare.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <cstdio>

//Used for sprite vertices
inline static void normalizeToRenderingTilePosition(glm::vec2& position, Tile* tile, float scale){
    position.x += tile->offset.x;
    position.y -= tile->offset.y;
    position *= scale;
    position.x -= - scale / 2;
    position.y -= 1 - scale / 2;
    position.y *= -1;
}

//Used for AABB calculations
inline static void normalizeToPhysicalTilePosition(glm::vec2& position, Tile* tile, float scale){
    position.x += tile->offset.x;
    position.y += tile->offset.y;
    position.y -= 1.0f / scale - 1.0f;
    position.y *= -1;
}

LevelGeometryData LevelLoader::loadGeometryData(std::string& path) {
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cout << "Could not open file: " << path << '\n';
        exit(1);
    }

    LevelGeometryData levelGeometryData;
    std::unordered_map<unsigned int, TilePositions> backgroundSprites;
    std::unordered_map<unsigned int, TilePositions> foregroundSprites;
    /* Maybe separate this 2 to 3 layers - Background, Middle ground and Foreground
     * What is background now should be middle ground.
     * There should not be any collision detection except in middle ground
     */
    size_t nRows;

    std::string line;
    size_t startIndex, endIndex;

    nRows = 20; //TODO
    float scale = 2.0f/(float)nRows;
    std::vector<std::vector<TileInstance>> terrainTiles;

    for(int i = 0; std::getline(inputFile, line); i++) {

        startIndex = 0;
        terrainTiles.emplace_back();

        for(int j = 0; ; j++) {
            endIndex = line.find(';', startIndex);
            if (endIndex == startIndex) { // There is no tile at this position (;;)
                startIndex = endIndex + 1;

                Tile* tile = Tiles::BLANK;
                glm::vec2 position = {j, i};
                normalizeToPhysicalTilePosition(position, tile, scale);
                glm::vec2 scaleVec = {scale, scale};
                terrainTiles[i].emplace_back(tile, position, scaleVec);
                continue;
            }

            if (endIndex == std::string::npos) break;
            unsigned int id = std::stoi(line.substr(startIndex, endIndex - startIndex));
            startIndex = endIndex + 1;

            // Tile exists in this pos
            Tile* tile = Global::tileManager->getAsset(id);
            if (backgroundSprites.find(id) == backgroundSprites.end())
                backgroundSprites[id] = TilePositions{tile};

            glm::vec2 position = {j, i};
            normalizeToRenderingTilePosition(position, tile, scale);
            backgroundSprites[id].positions.emplace_back(position.x, position.y);

            position = {j, i};
            normalizeToPhysicalTilePosition(position, tile, scale);
            glm::vec2 scaleVec = {scale, scale};
            terrainTiles[i].emplace_back(tile, position, scaleVec);
        }
    }

    Global::physicsEngine->registerTerrainTiles(terrainTiles);
    levelGeometryData.backgroundSpritePositions = backgroundSprites;
    levelGeometryData.foregroundSpritePositions = {};
    levelGeometryData.nRows = nRows;
    return levelGeometryData;
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

                EntityLiving* entity = new Nightmare({1.75f, -0.80f}); // TODO

                spawns.emplace_back(glm::vec2(posX, posY), entity, waveSpawnDelay);
            }

            room.weaves.emplace_back(spawnDelay, minEnemiesAliveForNext, spawns);
        }
        rooms.push_back(room);
    }
}
