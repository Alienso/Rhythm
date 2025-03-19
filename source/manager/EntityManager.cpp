//
// Created by Alienson on 21.8.2024..
//

#include "EntityManager.h"
#include "entity/enemy/Nightmare.h"
#include "reference/Global.h"

EntityManager::EntityManager() : player() {
    Global::entityManger = this;
    entitiesToDeSpawn.reserve(5);

    auto* nightmare = new Nightmare();
    loadedEntities.push_back(nightmare);
}

EntityManager::~EntityManager() {
    for(auto &loadedEntity : loadedEntities)
        delete loadedEntity;
}

void EntityManager::spawnEntity(EntityLiving *entity) {
    this->loadedEntities.push_back(entity);
}

void EntityManager::onUpdate(float deltaTime) {

    //TODO make entity updates less frequent?
    // TODO these are all pointers, so this is slow.
    for (auto& entity: loadedEntities){
        entity->onUpdate(deltaTime);
    }

    updateEntitiesToDeSpawn(deltaTime);

    player.onUpdate(deltaTime);

    if (onUpdateTimer > 0){
        onUpdateTimer-=deltaTime;
        return;
    }
    onUpdateTimer = 1.0f;

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
        if (entitiesToDeSpawn[i].timeToLive <= 0){
            for (size_t j = 0; j<loadedEntities.size(); j++ ){
                if (loadedEntities[j] == entitiesToDeSpawn[i].entity){
                    loadedEntities.erase(loadedEntities.begin() + (int)j);
                    break;
                }
            }
            EntityLiving* copy = entitiesToDeSpawn[i].entity;
            entitiesToDeSpawn.erase(entitiesToDeSpawn.begin() + (int)i);
            Global::physicsEngine->deleteEntity(copy);
            delete copy;
            break;
        }
    }
}
