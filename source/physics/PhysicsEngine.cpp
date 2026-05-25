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

    // TODO only check for those tiles around the entity, not every one.
    // Take initial pos and final pos, and make a rectangle out of it and only check for those ones
    // Use new struct (terrainTiles) it's coordinates hold the tile data
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

        int minX, minY, maxX, maxY;
        float scale = 0.1f;
        if (dx > 0){
            minX = (int)(entity->collisionBB.minX / scale);
            maxX = (int)((entity->collisionBB.maxX + dx) / scale);
        } else {
            minX = (int)((entity->collisionBB.minX + dx) / scale);
            maxX = (int)(entity->collisionBB.maxX / scale);
        }

        if (dy > 0){
            maxY = (int)(entity->collisionBB.minY / scale);
            minY = (int)((entity->collisionBB.maxY + dy) / scale);
        } else {
            maxY = (int)((entity->collisionBB.minY + dy) / scale);
            minY = (int)(entity->collisionBB.maxY / scale);
        }

        minY*=-1;
        maxY*=-1;

        for (int i = minY; i < maxY; i++) {
            for (int j = minX; j < maxX; j++) {
                AxisAlignedBB &box = terrainTiles[i][j].collisionBox;
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
        }

        // Y pass
        AxisAlignedBB bbY = bbX;
        bbY.translate({0.0f, dy});
        for (int i = minY; i < maxY; i++) {
            for (int j = minX; j < maxX; j++) {
                AxisAlignedBB &box = terrainTiles[i][j].collisionBox;
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
        }

        if (entity->pos().y + dy < -1){
            entity->moveTo(entity->pos().x + dx, -1);
        } else {
            entity->moveTo(entity->pos().x + dx, entity->pos().y + dy);
        }
    }
}

void PhysicsEngine::registerEntity(Entity *entity) {
    physicsEntities.push_back(entity);
}

void PhysicsEngine::removeEntity(Entity *entity) {
    for (size_t i=0; i < physicsEntities.size(); i++) {
        if (physicsEntities[i] == entity){
            physicsEntities.erase(physicsEntities.begin() + (int)i);
            return;
        }
    }
    assert(false);
}

void PhysicsEngine::registerTerrainTiles(std::vector<std::vector<TileInstance>>& terrainTiles_) {
    this->terrainTiles = terrainTiles_;

    terrainCollisionBoxes.clear();
    terrainCollisionBoxes.reserve(1024);
    for (auto &tileRows : terrainTiles_) {
        for (TileInstance& tile : tileRows) {
            if (tile.hasCollisionBox || tile.hasHurtBox)
                terrainCollisionBoxes.emplace_back(tile.collisionBox);
        }
    }
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