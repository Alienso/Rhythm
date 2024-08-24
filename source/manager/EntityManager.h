//
// Created by Alienson on 21.8.2024..
//

#ifndef RHYTHM_ENTITYMANAGER_H
#define RHYTHM_ENTITYMANAGER_H

#include "entity/Player.h"

class EntityManager {
public:
    EntityManager();
    ~EntityManager();

    void onUpdate(float deltaTime);
    void spawnEntity(EntityLiving* entity);

    Player player;
    std::vector<EntityLiving*> loadedEntities;
private:
    float onUpdateTimer = 0.0;

};



#endif //RHYTHM_ENTITYMANAGER_H
