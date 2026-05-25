//
// Created by Alienso on 10.8.2024.
//

#ifndef RHYTHM_PHYSICSENGINE_H
#define RHYTHM_PHYSICSENGINE_H


#include "render/sprite/Sprite.h"
#include "entity/Entity.h"
#include "level/Tile.h"

class PhysicsEngine {

public:

    PhysicsEngine();
    void onUpdate(float deltaTime);
    void registerEntity(Entity* entity);
    void removeEntity(Entity* entity);
    void registerTerrainTiles(std::vector<std::vector<TileInstance>>& terrainTiles);
    void deleteAllCollisionBoxes();

    [[nodiscard]] const std::vector<AxisAlignedBB>& getCollisionBoxes() const;

private:
    std::vector<Entity*> physicsEntities;

    //Both of these 2 need to be in sync.
    std::vector<AxisAlignedBB> terrainCollisionBoxes; //This one is for path tracing (projectiles)
    std::vector<std::vector<TileInstance>> terrainTiles; //This one is for collisions (optimization)

    static void limitEntitySpeed(Entity *entity);
};


#endif //RHYTHM_PHYSICSENGINE_H
