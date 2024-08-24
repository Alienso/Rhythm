//
// Created by Alienson on 24.8.2024..
//

#include "AiTaskWalkToPlayer.h"
#include "reference/Global.h"

AiTaskWalkToPlayer::AiTaskWalkToPlayer(Entity *entity) : entity(entity) {

}

bool AiTaskWalkToPlayer::shouldExecute() {
    return true;
}

bool AiTaskWalkToPlayer::shouldContinueExecuting() {
    return true;
}

void AiTaskWalkToPlayer::startExecuting() {
    AiTaskBase::startExecuting();
}

void AiTaskWalkToPlayer::updateTask() {
    float x = Global::player->pos.x*0.02f - entity->pos.x*0.02f;
    entity->pos += glm::vec2{x, 0}; //TODO have speed var?
    if (x < 0){
        entity->sprite.invertTex = false;
    }else{
        entity->sprite.invertTex = true;
    }

}
