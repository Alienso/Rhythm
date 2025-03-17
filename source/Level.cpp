//
// Created by Alienson on 1.8.2024..
//

#include <fstream>
#include "Level.h"
#include "reference/Reference.h"
#include "reference/Global.h"

struct TilePositions{
    TilePositions() : texture(nullptr){}
    explicit TilePositions(Texture* texture) : texture(texture){}
    Texture* texture;
    std::vector<glm::fvec2> positions;
};

Level::Level(const char* path) {

    std::unordered_map<int, TilePositions> tiles = load(path);

    //merge nearby tiles to one physics object

    //add those objects to physics engine
    glm::vec2 scaleVec = {tileScale, tileScale};
    for (auto& tile: tiles){
        for(glm::vec2& pos : tile.second.positions){
            Global::physicsEngine->registerCollisionBox({pos, scaleVec});
        }
    }
}

std::unordered_map<int, TilePositions> Level::load(const char * path) {

    //Load level data from file
    std::ifstream inputFile(path);
    std::string line;
    std::unordered_map<int, TilePositions> sprites;

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
            int id = std::stoi(line.substr(startIndex, endIndex - startIndex));
            startIndex = endIndex + 1;

            Texture* texture = Global::textureManager->getAsset(id);
            if (sprites.find(id) == sprites.end())
                sprites[id] = TilePositions{texture};
            sprites[id].positions.emplace_back(j, i);
        }
        nRows++;
    }

    float scale = 2.0f/(float)nRows;
    tileScale = scale;

    //Normalize offsets
    for(auto& sprite : sprites) {
        for (auto &position: sprite.second.positions) {
            position *= scale;
            position.x -= (float)Configuration::aspectRatio / 2.0f;
            position.x -= 1 - scale / 2;
            position.y -= 1 - scale / 2;
            position.y *= -1;
        }
    }

    //Create sprites
    int i=0;
    tileSprites.reserve(sprites.size());
    for(auto& sprite : sprites){
        tileSprites.emplace_back();
        tileSprites[i].initialize(sprite.second.texture, sprite.second.positions, scale/2);
        i++;
    }

    return sprites;
}

void Level::onRender() {
    background.onRender();

    for(auto& sprite : tileSprites)
        sprite.onRender();
}

void Level::onUpdate(float deltaTime) {
    background.translate(0.1f * deltaTime);
}
