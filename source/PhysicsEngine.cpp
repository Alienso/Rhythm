//
// Created by Alienson on 10.8.2024..
//

#include "PhysicsEngine.h"
#include "reference/Global.h"

PhysicsEngine::PhysicsEngine() {
    Global::physicsEngine = this;
}

void PhysicsEngine::onUpdate(float deltaTime) {

    for (Entity* entity: entities) {
        float gravityStr = 9.81;
        if (entity->movementVec.y < 0)
            gravityStr*=1.5;
        entity->movementVec.y -= gravityStr * deltaTime;

        entity->pos.x += entity->movementVec.x * entity->speedModifier * deltaTime; //TODO move this somewhere else since this fields need to go to EntityLiving
        entity->pos.y += entity->movementVec.y * entity->speedModifier * deltaTime;

        if (entity->pos.y - (entity->sprite.scale.y) <= -0.9f) {
            entity->pos.y = -0.9f + (entity->sprite.scale.y);
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
