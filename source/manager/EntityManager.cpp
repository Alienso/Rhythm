//
// Created by Alienson on 21.8.2024..
//

#include "EntityManager.h"
#include "entity/enemy/Nightmare.h"
#include "reference/Global.h"

EntityManager::EntityManager() : player() {
    Global::entityManger = this;

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
        if (!entity->isAlive){
            //loadedEntities.remove(entity);//TODO
        }
        entity->onUpdate(deltaTime);
    }

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
