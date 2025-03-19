//
// Created by Alienson on 18.3.2025..
//

#include "RayTrace.h"
#include "reference/Global.h"


RayTraceResult RayTracer::rayTrace(glm::vec2 pos, glm::vec2 dest){
    RayTraceResult result;
    float closest = 99.0f;
    glm::vec2 rayDir = glm::normalize(glm::vec2{ dest.x - pos.x, dest.y - pos.y });

    float xDiff = dest.x - pos.x;
    float yDiff = dest.y - pos.y;

    if (xDiff == 0){
        //special case when line is ~parallel
        return result; //TODO
    }
    if (yDiff == 0){
        //special case when y = const
        return result; //TODO
    }

    float k = yDiff / xDiff;
    float n = - pos.x * k + pos.y; //TODO why is this -pos.x??
    glm::vec2 kn = {k, n};

    for (EntityLiving* entity : Global::entityManger->loadedEntities){
        float dist = intersect(pos, rayDir, kn, entity->collisionBB);
        if (dist < closest){
            closest = dist;
            result.entityHit = entity;
            result.hitType = HIT_TYPE_ENTITY;
        }
    }

    for (const AxisAlignedBB& aabb : Global::physicsEngine->getCollisionBoxes()){
        float dist = intersect(pos, rayDir, kn, aabb);
        if (dist < closest){
            closest = dist;
            result.blockHit = &aabb;
            result.hitType = HIT_TYPE_BLOCK;
        }
    }

    result.distance = closest;
    result.hitPoint = {pos.x + rayDir.x * closest, pos.y + rayDir.y * closest};
    return result;
}

inline float RayTracer::intersect(glm::vec2& pos, glm::vec2& rayDir, glm::vec2& kn, const AxisAlignedBB& aabb){
    if (rayDir.x > 0 && rayDir.y > 0 && (pos.x > aabb.maxX || pos.y > aabb.maxY)) //TOP RIGHT
        return 999.0f;
    if (rayDir.x > 0 && rayDir.y < 0 && (pos.x > aabb.maxX || pos.y < aabb.minY)) //BOTTOM RIGHT
        return 999.0f;
    if (rayDir.x < 0 && rayDir.y > 0 && (pos.x < aabb.minX || pos.y > aabb.maxY)) //TOP LEFT
        return 999.0f;
    if (rayDir.x < 0 && rayDir.y < 0 && (pos.x < aabb.minX || pos.y < aabb.minY)) //BOTTOM LEFT
        return 999.0f;

    float distance = 999.0f;
    float minDistance = distance;
    //we know rectangle is in the same quarter as the ray is shooting at
    //TOP y = maxY
    float x = (aabb.maxY - kn.y) / kn.x;
    if (x > aabb.minX && x < aabb.maxX)
        minDistance = glm::distance(pos, glm::vec2{x, aabb.maxY});
    //BOTTOM y = minY
    x = (aabb.minY - kn.y) / kn.x;
    if (x > aabb.minX && x < aabb.maxX) {
        distance = glm::distance(pos, glm::vec2{x, aabb.minY});
        if (distance < minDistance) minDistance = distance;
    }
    //LEFT x = minX
    float y = kn.x * aabb.minX + kn.y;
    if (y > aabb.minY && y < aabb.maxY) {
        distance = glm::distance(pos, glm::vec2{aabb.minX, y});
        if (distance < minDistance) minDistance = distance;
    }
    //RIGHT x = maxX
    y = kn.x * aabb.maxX + kn.y;
    if (y > aabb.minY && y < aabb.maxY) {
        distance = glm::distance(pos, glm::vec2{aabb.maxX, y});
        if (distance < minDistance) minDistance = distance;
    }

    return minDistance;
}


