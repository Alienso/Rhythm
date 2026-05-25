//
// Created by Alienso on 21.8.2024.
//

#include "EntityManager.h"
#include "entity/enemy/Nightmare.h"
#include "reference/Global.h"

EntityManager::EntityManager() : player( {1.75, -0.80 }) {
    Global::entityManger = this;
    entitiesToDeSpawn.reserve(10);
}

EntityManager::~EntityManager() {
    for(auto &loadedEntity : loadedEntities) {
        delete loadedEntity;
    }
}

void EntityManager::spawnEntity(EntityLiving *entity) {
    this->loadedEntities.push_back(entity);
}

void EntityManager::onUpdate(float deltaTime) {

    for (auto& entity: loadedEntities){
        entity->onUpdate(deltaTime);
    }

    updateEntitiesToDeSpawn(deltaTime);

    player.onUpdate(deltaTime);
}

void EntityManager::onRender() const {
    for (EntityLiving* entity : loadedEntities){
        entity->onRender();
    }
    player.onRender();
}

void EntityManager::scheduleDeSpawn(EntityLiving *entity, float time) {
    entitiesToDeSpawn.emplace_back(entity, time);
}

void EntityManager::updateEntitiesToDeSpawn(float deltaTime) {
    for (size_t i = 0; i < entitiesToDeSpawn.size(); i++){
        entitiesToDeSpawn[i].timeToLive -= deltaTime;
        if (entitiesToDeSpawn[i].timeToLive > 0) {
            continue;
        }

        for (size_t j = 0; j < loadedEntities.size(); j++) {
            if (loadedEntities[j] == entitiesToDeSpawn[i].entity) {
                loadedEntities.erase(loadedEntities.begin() + (int)j);
                break;
            }
        }

        EntityLiving* copy = entitiesToDeSpawn[i].entity;
        //TODO Try make it so entity can be deleted from a single point in code. Here we jump to loadedEntities, entitiesToDeSpawn, physicsEngine, ...
        entitiesToDeSpawn.erase(entitiesToDeSpawn.begin() + (int)i);
        Global::physicsEngine->removeEntity(copy); //TODO what if entity does not exist in physicsEngine.

        Global::currentLevel->getCurrentRoom().getCurrentWeave().enemiesLeft--; //TODO This is not safe
        assert(Global::currentLevel->getCurrentRoom().getCurrentWeave().enemiesLeft >= 0);

        delete copy;
        // This break is intentional, not sure why. Probably related to enemy waves.
        // This shouldn't affect much since this will be called every frame
        break;
    }
}
