//
// Created by Alienson on 10.8.2024..
//

#include "Entity.h"
#include "reference/Reference.h"
#include "render/UiRenderer.h"

Entity::Entity(Texture *texture) : sprite(texture), collisionSprite(Textures::COLLISION_BOX) {
    sprite.parent = this;
    collisionSprite.parent = this;
    collisionSprite.scale = {0,0};
}

Entity::~Entity() {

}

void Entity::onRender() const {
    sprite.onRender();
    if (UiRenderer::renderHitBoxes)
        collisionSprite.onRender();
}

void Entity::onUpdate(float deltaTime) {

}
