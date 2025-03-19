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

        if (entity->pos.y - (entity->sprite.scale.y) <= -1.0f && entity->movementVec.y < 0) {
            entity->pos.y = -1.0f + (entity->sprite.scale.y);
            entity->movementVec.y = 0;
            entity->onGround = true;
        }

        if (entity->movementVec.y < 0)
            for (AxisAlignedBB box: collisionBoxes)
                if (box.intersects(entity->collisionBB)) {
                    entity->pos.y = box.maxY + entity->sprite.scale.y - 0.001f; //TODO this needs to be adjusted scale(texture based) instead of real one
                    entity->movementVec.y = 0;
                    entity->onGround = true;
                    break;
                }

        if (entity->pos.x > Configuration::aspectRatio)
            entity->pos.x = Configuration::aspectRatio;
        if (entity->pos.x < -Configuration::aspectRatio)
            entity->pos.x = -Configuration::aspectRatio;
    }
}

void PhysicsEngine::registerEntity(Entity *entity) {
    entities.push_back(entity);
}

void PhysicsEngine::deleteEntity(Entity *entity) {
    for (size_t i=0; i<entities.size(); i++){
        if (entities[i] == entity){
            entities.erase(entities.begin() + (int)i);
            return;
        }
    }
    assert(false);
}

void PhysicsEngine::registerCollisionBox(AxisAlignedBB box) {
    collisionBoxes.push_back(box);
}

const std::vector<AxisAlignedBB> &PhysicsEngine::getCollisionBoxes() const {
    return collisionBoxes;
}
