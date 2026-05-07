//
// Created by Alienso on 10.8.2024.
//

#include "PhysicsEngine.h"
#include "reference/Global.h"

PhysicsEngine::PhysicsEngine() {
    Global::physicsEngine = this;
}

void PhysicsEngine::onUpdate(float deltaTime) {

    static const float eps = 0.000001f;

    for (Entity* entity : physicsEntities) {
        if (!entity->onGround) {
            float gravityStr = Configuration::gravityStrength;
            if (entity->movementVec.y < 0.0f)
                gravityStr *= Configuration::gravityFallMultiplier;
            entity->movementVec.y -= gravityStr * deltaTime;
        }
        entity->onGround = false;

        limitEntitySpeed(entity);

        entity->previousPos = entity->pos();

        float dx = entity->movementVec.x * entity->speedModifier * deltaTime;
        float dy = entity->movementVec.y * deltaTime;

        // X pass
        AxisAlignedBB bbX = entity->collisionBB;
        bbX.translate({dx, 0.0f});
        for (const AxisAlignedBB& box : terrainCollisionBoxes) {
            if (!box.intersects(bbX)) continue;
            float xDiff = (box.getWidth() + bbX.getWidth())
                          - std::max(bbX.maxX - box.minX, box.maxX - bbX.minX);
            float yDiff = (box.getHeight() + bbX.getHeight())
                          - std::max(bbX.maxY - box.minY, box.maxY - bbX.minY);
            if (xDiff >= yDiff) continue; // floor/ceiling — defer to Y pass
            float sign = (bbX.getCenter().x >= box.getCenter().x) ? 1.0f : -1.0f;
            float correction = sign * (xDiff - eps);
            bbX.translate({correction, 0.0f});
            dx += correction;
            entity->movementVec.x = 0.0f;
        }

        // Y pass
        AxisAlignedBB bbY = bbX;
        bbY.translate({0.0f, dy});
        for (const AxisAlignedBB& box : terrainCollisionBoxes) {
            if (!box.intersects(bbY)) continue;
            float xDiff = (box.getWidth() + bbY.getWidth())
                          - std::max(bbY.maxX - box.minX, box.maxX - bbY.minX);
            float yDiff = (box.getHeight() + bbY.getHeight())
                          - std::max(bbY.maxY - box.minY, box.maxY - bbY.minY);
            if (xDiff < yDiff) continue; // wall — already handled by X pass
            float sign = (bbY.getCenter().y >= box.getCenter().y) ? 1.0f : -1.0f;
            float correction = sign * (yDiff - eps);
            bbY.translate({0.0f, correction});
            dy += correction;
            entity->movementVec.y = 0.0f;
            if (correction > 0.0f)
                entity->onGround = true;
        }

        entity->moveTo(entity->pos().x + dx, entity->pos().y + dy);
    }
}

void PhysicsEngine::registerEntity(Entity *entity) {
    physicsEntities.push_back(entity);
}

void PhysicsEngine::removeEntity(Entity *entity) {
    for (size_t i=0; i < physicsEntities.size(); i++){
        if (physicsEntities[i] == entity){
            physicsEntities.erase(physicsEntities.begin() + (int)i);
            return;
        }
    }
    assert(false);
}

void PhysicsEngine::registerCollisionBox(AxisAlignedBB box) {
    terrainCollisionBoxes.push_back(box);
}

const std::vector<AxisAlignedBB> &PhysicsEngine::getCollisionBoxes() const {
    return terrainCollisionBoxes;
}

void PhysicsEngine::deleteAllCollisionBoxes() {
    terrainCollisionBoxes.clear();
}

void PhysicsEngine::limitEntitySpeed(Entity *entity) {
    if (entity->movementVec.y < -Configuration::maxYSpeed)
        entity->movementVec.y = -Configuration::maxYSpeed;
    if (entity->movementVec.y > Configuration::maxYSpeed)
        entity->movementVec.y = Configuration::maxYSpeed;
    if (entity->movementVec.x < -Configuration::maxXSpeed)
        entity->movementVec.x = -Configuration::maxXSpeed;
    if (entity->movementVec.x > Configuration::maxXSpeed)
        entity->movementVec.x = Configuration::maxXSpeed;
}