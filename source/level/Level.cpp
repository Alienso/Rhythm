//
// Created by Alienson on 1.8.2024..
//

#include "Level.h"
#include "reference/Reference.h"
#include "reference/Global.h"

#include <fstream>


Level::Level(const char* path) {

    std::unordered_map<unsigned int, TilePositions> tiles;
    load(path, tiles);

    //merge nearby tiles to one physics object

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
}

void Level::load(const char * path, std::unordered_map<unsigned int, TilePositions>& sprites) {

    //Load level data from file
    std::ifstream inputFile(path);
    std::string line;

    size_t startIndex, endIndex;
    size_t nRows = 0;

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

    float scale = 2.0f/(float)nRows;
    tileScale = scale;

    //Normalize offsets
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
    background.translate(0.1f * deltaTime);
}

void Level::increaseScore(unsigned int amount, float scoreMultiplier) {
    score+= amount * Global::player->getRhythmMultiplier()->score * scoreMultiplier;
}
