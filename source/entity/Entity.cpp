//
// Created by Alienson on 10.8.2024..
//

#include "Entity.h"
#include "reference/Reference.h"

Entity::Entity(Texture *texture) : sprite(texture) {
    sprite.parent = this;
}

Entity::~Entity() {

}

void Entity::onRender() const {
    sprite.onRender();
}

void Entity::onUpdate() {

}
