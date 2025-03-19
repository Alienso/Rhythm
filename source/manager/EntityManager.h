//
// Created by Alienson on 21.8.2024..
//

#ifndef RHYTHM_ENTITYMANAGER_H
#define RHYTHM_ENTITYMANAGER_H

#include "entity/Player.h"

//TODO
struct EntityDeSpawn{
    EntityDeSpawn(EntityLiving* entityLiving, float timeToLive) : entity(entityLiving), timeToLive(timeToLive){}
    EntityLiving* entity;
    float timeToLive;
};

class EntityManager {
public:
    EntityManager();
    ~EntityManager();

    void onUpdate(float deltaTime);
    void onRender() const;

    void spawnEntity(EntityLiving* entity);
    void scheduleDeSpawn(EntityLiving* entity, float time = 3);

    Player player;
    std::vector<EntityLiving*> loadedEntities;
    std::vector<EntityDeSpawn> entitiesToDeSpawn;
private:
    float onUpdateTimer = 0.0;

    void updateEntitiesToDeSpawn(float deltaTime);

};



#endif //RHYTHM_ENTITYMANAGER_H
