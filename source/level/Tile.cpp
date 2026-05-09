//
// Created by Alienso on 23.3.2025.
//

#include "Tile.h"

Tile::Tile(unsigned int ID, Texture* texture, bool hasCollisionBox, bool hasHurtBox) :
    ID(ID),
    texture(texture),
    hasCollisionBox(hasCollisionBox),
    hasHurtBox(hasHurtBox) {

}

Tile::Tile(unsigned int ID, Texture* texture, bool hasCollisionBox, bool hasHurtBox, const glm::vec2 offset, const glm::vec2 scale) :
        ID(ID),
        texture(texture),
        scale(scale),
        offset(offset),
        hasCollisionBox(hasCollisionBox),
        hasHurtBox(hasHurtBox) {

}

void Tile::setDamage(float damage_) {
    this->damage = damage_;
}

float Tile::getDamage() const {
    return damage;
}

TileInstance::TileInstance(Tile* tile, const glm::vec2 pos){
    hasCollisionBox = tile->hasCollisionBox;
    hasHurtBox = tile->hasHurtBox;

    if (hasCollisionBox) {
        collisionBox = {
                pos.x + tile->offset.x,
                pos.y + tile->offset.y,
                pos.x + tile->scale.x + tile->offset.x,
                pos.y + tile->scale.y + tile->offset.y
        };
    }
    if (hasHurtBox) {
        hurtBox = {
                pos.x + tile->offset.x,
                pos.y + tile->offset.y,
                pos.x + tile->scale.x + tile->offset.x,
                pos.y + tile->scale.y + tile->offset.y,
                tile->getDamage()
        };
    }
}