//
// Created by Alienson on 18.3.2025..
//

#ifndef RHYTHM_RAYTRACE_H
#define RHYTHM_RAYTRACE_H


#include "entity/Entity.h"

enum RayTraceHitType{
    HIT_TYPE_BLOCK, HIT_TYPE_ENTITY, HIT_TYPE_MISS
};

class RayTraceResult {
public:
        Entity* entityHit = nullptr;
        const AxisAlignedBB* blockHit = nullptr;
        float distance;
        glm::vec2 hitPoint;
        RayTraceHitType hitType = HIT_TYPE_MISS;
};

class RayTracer{

public:
    static RayTraceResult rayTrace(glm::vec2 pos, glm::vec2 dest);

private:
    static inline float intersect(glm::vec2& pos, glm::vec2& rayDir, glm::vec2& kn, const AxisAlignedBB& aabb);

};


#endif //RHYTHM_RAYTRACE_H
