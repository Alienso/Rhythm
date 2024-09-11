//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_PHYSICSENGINE_H
#define RHYTHM_PHYSICSENGINE_H


#include "entity/Sprite.h"
#include "entity/Entity.h"

class PhysicsEngine {

public:

    PhysicsEngine();
    void onUpdate(float deltaTime);
    void registerEntity(Entity* entity);
    void registerCollisionBox(AxisAlignedBB box);

private:
    std::vector<Entity*> entities;
    std::vector<AxisAlignedBB> collisionBoxes; //for terrain
};


#endif //RHYTHM_PHYSICSENGINE_H
