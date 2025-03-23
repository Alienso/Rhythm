//
// Created by Alienson on 23.3.2025..
//

#include "Tile.h"

Tile::Tile(unsigned int ID, Texture* texture, bool hasCollisionBox, bool hasHurtBox) : ID(ID), texture(texture), hasCollisionBox(hasCollisionBox), hasHurtBox(hasHurtBox) {

}

Tile::Tile(unsigned int ID, Texture* texture, bool hasCollisionBox, bool hasHurtBox, const glm::vec2 offset, const glm::vec2 scale) :
        ID(ID), texture(texture), scale(scale), offset(offset), hasCollisionBox(hasCollisionBox), hasHurtBox(hasHurtBox) {
    if (hasCollisionBox)
        collisionBox = {offset.x, offset.y, scale.x + offset.x, scale.y + offset.y};
    if (hasHurtBox)
        hurtBox = {offset.x, offset.y, scale.x + offset.x, scale.y + offset.y, 1.0};
}
