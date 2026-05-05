//
// Created by Alienson on 1.8.2024..
//

#include "Level.h"
#include "reference/Reference.h"
#include "reference/Global.h"
#include "LevelLoader.h"

#include <fstream>


Level::Level(const char* path) {

    std::unordered_map<unsigned int, TilePositions> tiles;
    loadTiles(path, tiles);

    //TODO merge nearby tiles to one physics object
    //add those objects to physics engine
    for (auto& entry: tiles){
        glm::vec2 scaleVec = {tileScale * entry.second.tile->scale.x, tileScale * entry.second.tile->scale.y};
        if (entry.second.tile->hasCollisionBox) {
            for (glm::vec2 &pos: entry.second.positions) {
                Global::physicsEngine->registerCollisionBox({pos, scaleVec});
            }
        } /*else if (entry.second.tile->hasHurtBox){
            for (glm::vec2 &pos: entry.second.positions) {
                Global::physicsEngine->registerHurtBox({pos, scaleVec});
            }
        }*/ //TODO
    }

    LevelLoader::loadRooms(path, rooms);
}

Level::~Level() {
    Global::physicsEngine->deleteAllCollisionBoxes();

    tileScale = 0.0f;
    tileSprites.clear();

    //TODO maybe delete all except player?
    for (const Room& room : rooms)
        for (const Weave& weave : room.weaves)
            for (const Spawn& spawn : weave.spawns)
                Global::entityManger->scheduleDeSpawn(spawn.entity, 0.0f);
    currentRoomIndex = 0;
    rooms.clear();
}

void Level::loadTiles(const char * path, std::unordered_map<unsigned int, TilePositions>& sprites) {

    //Load level data from file
    size_t nRows = 0;
    LevelLoader::loadGeometryData(path, sprites, nRows);

    float scale = 2.0f/(float)nRows;
    tileScale = scale;

    //Normalize offsets
    //TODO 1st column is offscreen
    for(auto& entry : sprites) {
        for (auto &position: entry.second.positions) {
            position.x += entry.second.tile->offset.x;
            position.y -= entry.second.tile->offset.y;
            position *= scale;
            position.x -= Configuration::aspectRatio / 2.0f;
            position.x -= 1 - scale / 2;
            position.y -= 1 - scale / 2;
            position.y *= -1;
        }
    }


    //Create sprites
    unsigned int i=0;
    tileSprites.reserve(sprites.size());
    for(auto& entry : sprites){
        tileSprites.emplace_back();
        tileSprites[i].initialize(entry.second.tile->texture, entry.second.positions, glm::vec2{entry.second.tile->scale * scale * 0.5f} );
        i++;
    }
}

void Level::onRender() {
    background.onRender();

    for(auto& sprite : tileSprites)
        sprite.onRender();
}

void Level::onUpdate(float deltaTime) {
    if (false){ //TODO
        this->currentRoomIndex++;
    }
    Room& currentRoom = getCurrentRoom();
    currentRoom.onUpdate(deltaTime);
}

void Level::increaseScore(unsigned int amount, float scoreMultiplier) {
    score += amount * Global::player->getCurrentRhythmMultiplier()->scoreMultiplier * scoreMultiplier;
}

Room &Level::getCurrentRoom() {
    return rooms[currentRoomIndex];
}
