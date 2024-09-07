//
// Created by Alienson on 1.8.2024..
//

#include "Level.h"
#include "reference/Reference.h"

struct TilePositions{
    TilePositions() : texture(nullptr){}
    explicit TilePositions(Texture* texture) : texture(texture){}
    Texture* texture;
    std::vector<glm::vec2> positions;
};

Level::Level() {
    //load ids from file

    //create vector of ids for each type of texture

    //create offsets for this vector

    std::string file = "111111111";
    std::unordered_map<int, TilePositions> sprites;
    /*for (size_t i = 0; i<file.size(); i++){
        int id = 1;
        glm::vec2 pos{1,1};
        if (sprites.find(id) == sprites.end()){
            sprites[id] = TilePositions{Textures::BLANK};
        }else{
            sprites[id].positions.emplace_back(1,1);
        }
    }*/

    std::vector<glm::fvec2> offsets;
    offsets.reserve(100);
    float offset = 0.1f;
    for(int y = -10; y < 10; y += 2){
        for(int x = -10; x < 10; x += 2){
            glm::fvec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            offsets.push_back(translation);
        }
    }
    spriteInstanced.initialize(Textures::CURSOR, offsets, 0.05f);

    //merge nearby tiles to one physics object

    //add those objects to physics engine
}

void Level::onRender() {
    background.onRender();
    spriteInstanced.onRender();
}

void Level::onUpdate(float deltaTime) {
    background.translate(0.1f * deltaTime);
}
