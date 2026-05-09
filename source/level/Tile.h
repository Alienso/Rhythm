//
// Created by Alienso on 23.3.2025.
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

    void setDamage(float damage);
    float getDamage() const;

    unsigned int ID;

    Texture* texture;

    //Vertices related
    glm::vec2 scale = {1.0, 1.0}; // e.g. in case of a vertical plank set to (1.0, 0.5)
    glm::vec2 offset = {0.0, 0.0}; // In case when texture is not centered, offsets the vertices by this amount

    bool hasCollisionBox = false;
    bool hasHurtBox = false;

    float damage = 0.0f;
};

class TileInstance {
public:
    TileInstance(Tile* tile, const glm::vec2 pos);

    Tile* tile;
    AxisAlignedBB collisionBox;
    AxisAlignedHB hurtBox;
    bool hasCollisionBox = false;
    bool hasHurtBox = false;
};

struct TilePositions {
    TilePositions() : tile(nullptr){}
    explicit TilePositions(Tile* tile) : tile(tile){}
    Tile* tile;
    std::vector<glm::fvec2> positions;
};


#endif //RHYTHM_TILE_H
