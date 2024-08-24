//
// Created by Alienson on 21.8.2024..
//

#include "EntityManager.h"
#include "entity/enemy/Nightmare.h"
#include "reference/Global.h"

EntityManager::EntityManager() : player() {
    Global::entityManger = this;

    Nightmare* nightmare = new Nightmare();
    loadedEntities.push_back(nightmare);
}

EntityManager::~EntityManager() {
    for(auto &loadedEntity : loadedEntities)
        delete loadedEntity;
}

void EntityManager::spawnEntity(Entity *entity) {
    this->loadedEntities.push_back(entity);
}

void EntityManager::onUpdate(float deltaTime) {

    //TODO make entity updates less frequent?
    for (auto& entity: loadedEntities){
        /*if (entity.isDead){ //TODO
            loadedEntities.remove(entity);
        }*/
        entity->onUpdate();
    }

    if (onUpdateTimer > 0){
        onUpdateTimer-=deltaTime;
        return;
    }
    onUpdateTimer = 1.0f;

}
