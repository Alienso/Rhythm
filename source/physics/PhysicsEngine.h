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
    void deleteEntity(Entity* entity);
    void registerCollisionBox(AxisAlignedBB box);

    [[nodiscard]] const std::vector<AxisAlignedBB>& getCollisionBoxes() const;

private:
    std::vector<Entity*> entities;
    std::vector<AxisAlignedBB> collisionBoxes; //for terrain
};


#endif //RHYTHM_PHYSICSENGINE_H
