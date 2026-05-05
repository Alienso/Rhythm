//
// Created by Alienson on 10.8.2024..
//

#include "Entity.h"
#include "reference/Reference.h"
#include "render/UiRenderer.h"

Entity::Entity(Texture *texture) : sprite(texture), collisionSprite(Textures::COLLISION_BOX) {
    sprite.parent = this;
    collisionSprite.scale = {0,0};
}

Entity::~Entity() { //Do not delete, it is virtual

}

void Entity::onRender() const {
    sprite.onRender();
    if (UiRenderer::showCollisionBoxes)
        collisionSprite.onRender();
}

void Entity::onUpdate(float deltaTime) {
}

void Entity::moveTo(float x, float y) {
    pos_.x = x;
    pos_.y = y;
    rebuildCollisionBoxes();
}

void Entity::moveBy(float x, float y) {
    pos_.x += x;
    pos_.y += y;
    rebuildCollisionBoxes();
}

void Entity::rebuildCollisionBoxes() {

}

const glm::vec2 &Entity::pos() const {
    return pos_;
}
