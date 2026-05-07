//
// Created by Alienso on 10.8.2024.
//

#ifndef RHYTHM_PHYSICSENGINE_H
#define RHYTHM_PHYSICSENGINE_H


#include "render/sprite/Sprite.h"
#include "entity/Entity.h"

class PhysicsEngine {

public:

    PhysicsEngine();
    void onUpdate(float deltaTime);
    void registerEntity(Entity* entity);
    void removeEntity(Entity* entity);
    void registerCollisionBox(AxisAlignedBB box);
    void deleteAllCollisionBoxes();

    [[nodiscard]] const std::vector<AxisAlignedBB>& getCollisionBoxes() const;

private:
    std::vector<Entity*> physicsEntities;
    std::vector<AxisAlignedBB> terrainCollisionBoxes;

    void limitEntitySpeed(Entity *entity);
};


#endif //RHYTHM_PHYSICSENGINE_H
