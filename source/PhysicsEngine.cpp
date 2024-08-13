//
// Created by Alienson on 10.8.2024..
//

#include "PhysicsEngine.h"
#include "reference/Global.h"

PhysicsEngine::PhysicsEngine() {
    entities.push_back(Global::player);
}

void PhysicsEngine::onUpdate(float deltaTime) {

    for (Entity* entity: entities) {
        entity->movementVec.y -= 9.81f * deltaTime;

        entity->pos.x += entity->movementVec.x * entity->speedModifier * deltaTime;
        entity->pos.y += entity->movementVec.y * entity->speedModifier * deltaTime;

        if (entity->pos.y <= -0.9) {
            entity->pos.y = -0.9;
            entity->movementVec.y = 0;
            entity->onGround = true;
        }

        if (entity->pos.x > 1)
            entity->pos.x = 1;
        if (entity->pos.x < -1)
            entity->pos.x = -1;

    }
}

void PhysicsEngine::registerEntity(Entity *entity) {
    entities.push_back(entity);
}
