//
// Created by Alienson on 23.3.2025..
//

#ifndef RHYTHM_TILE_H
#define RHYTHM_TILE_H

#include <glm/glm.hpp>
#include "render/Texture.h"
#include "physics/AxisAlignedBB.h"


class Tile {
public:
    Tile(unsigned int ID, Texture* texture, bool hasCollisionBox = true, bool hasHurtBox = false);
    Tile(unsigned int ID, Texture* texture, bool hasCollisionBox, bool hasHurtBox, glm::vec2 offset, glm::vec2 scale);

    unsigned int ID;

    Texture* texture;
    AxisAlignedBB collisionBox;
    AxisAlignedHB hurtBox;

    glm::vec2 scale = {1.0, 1.0};
    glm::vec2 offset = {0.0, 0.0};

    bool hasCollisionBox = false;
    bool hasHurtBox = false;

private:

};

struct TilePositions {
    TilePositions() : tile(nullptr){}
    explicit TilePositions(Tile* tile) : tile(tile){}
    Tile* tile;
    std::vector<glm::fvec2> positions;
};


#endif //RHYTHM_TILE_H
