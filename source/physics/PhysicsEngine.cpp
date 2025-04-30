//
// Created by Alienson on 10.8.2024..
//

#include "PhysicsEngine.h"
#include "reference/Global.h"
#include "RayTrace.h"

PhysicsEngine::PhysicsEngine() {
    Global::physicsEngine = this;
}

void PhysicsEngine::onUpdate(float deltaTime) {

    for (Entity* entity: entities) {
        if (!entity->onGround) {
            float gravityStr = gravityStrengthBase;
            if (entity->movementVec.y < 0)
                gravityStr *= 1.5;
            entity->movementVec.y -= gravityStr * deltaTime;
        }
        entity->onGround = false;

        if (entity->pos().y - (entity->sprite.scale.y) <= -1.0f && entity->movementVec.y <= 0) {
            entity->moveTo(entity->pos().x, -1.0f + (entity->sprite.scale.y));
            entity->movementVec.y = 0;
            entity->onGround = true;
        }

        if (glm::abs(entity->movementVec.y) > 10){
            entity->movementVec.y = 10;
        }

        entity->previousPos = entity->pos();
        glm::vec2 nextPos = { entity->pos().x + entity->movementVec.x * entity->speedModifier * deltaTime, entity->pos().y + entity->movementVec.y * deltaTime};
        AxisAlignedBB nextCollisionBox = entity->collisionBB;
        nextCollisionBox.translate({entity->movementVec.x * entity->speedModifier * deltaTime, entity->movementVec.y * deltaTime});

        //TODO FIX THIS RUBBISH
        bool hitHorizontal = false, hitVertical = false;
        EnumSide sideHit = SIDE_NONE;
        static const float eps = 0.000001f;
        for (AxisAlignedBB box: collisionBoxes){
            if (box.intersects(nextCollisionBox)) {
                //TODO this cant detect falling through platforms
                //float vx, vy. If vx>aabb.x || vy>aabb.y, for each segment, move aabb by {aabb.x, aabb.y} and check collision

                float xDiff = (box.getWidth() + nextCollisionBox.getWidth()) - std::max(nextCollisionBox.maxX - box.minX , box.maxX - nextCollisionBox.minX);
                float yDiff = (box.getHeight() + nextCollisionBox.getHeight()) - std::max(nextCollisionBox.maxY - box.minY, box.maxY - nextCollisionBox.minY);

                glm::vec2 v = nextCollisionBox.getCenter() - entity->collisionBB.getCenter();
                float vx = v.x;
                float vy = v.y;

                bool shouldContinue = true;
                if (glm::abs(vy) < 0.002 && vy != 0){
                    float sign;
                    if (vy > 0){
                        sideHit = SIDE_BOTTOM;
                        sign = -1.0f;
                    }else {
                        sideHit = SIDE_TOP;
                        sign = 1.0f;
                        entity->onGround = true;
                    }
                    nextCollisionBox.translate({0, (yDiff - eps) * sign});
                    nextPos.y += (yDiff - eps) * sign;
                    vy = 0;
                    hitHorizontal = true;
                    entity->movementVec.y = 0; //TODO
                    shouldContinue = false;
                }
                if (glm::abs(vx) < 0.002 && vx != 0){
                    float sign;
                    if (vx > 0){
                        sideHit = SIDE_LEFT;
                        sign = 1.0f;
                    }else{
                        sideHit = SIDE_RIGHT;
                        sign = -1.0f;
                    }
                    nextCollisionBox.translate({(xDiff - eps) * sign, 0});
                    nextPos.x += (xDiff - eps) * sign;
                    vx = 0;
                    hitVertical = true;
                    shouldContinue = false;
                    entity->movementVec.x = 0;
                }

                if (!shouldContinue){
                    continue;
                }

                float t1 = glm::abs(vx) < eps ? 9999 : glm::abs(xDiff / vx);
                float t2 = glm::abs(vy) < eps ? 9999 : glm::abs(yDiff / vy);
                float t = t1 < t2 ? t1 : t2;

                glm::vec2 moveVec = -t * glm::vec2{vx, vy}; //using (-vx * deltaTime) allows movement while this blocks it
                if (yDiff < 0.0001)
                    moveVec.x = 0;
                if (xDiff < 0.0001)
                     moveVec.y = 0;
                nextCollisionBox.translate(moveVec); //we move in the opposite direction
                nextPos += moveVec;
                //Now it shouldn't collide with anything

                if (xDiff < yDiff){
                    sideHit = vx > 0 ? SIDE_LEFT : SIDE_RIGHT;
                    hitHorizontal = true;
                } else {
                    sideHit = vy > 0 ? SIDE_BOTTOM : SIDE_TOP;
                    entity->movementVec.y = 0; //TODO
                    hitVertical = true;
                    if (sideHit == SIDE_TOP)
                        entity->onGround = true;
                }

                if (hitHorizontal && hitVertical)
                    break;
            }
        }

        //2 sideHit needs to exist
        if (sideHit == SIDE_TOP){
            entity->movementVec.y = 0;
            entity->onGround = true;
        }

        entity->moveTo(nextPos.x, nextPos.y);
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
