//
// Created by Alienson on 24.8.2024..
//

#include "AiTaskWalkToPlayer.h"
#include "reference/Global.h"

AiTaskWalkToPlayer::AiTaskWalkToPlayer(EntityLiving *entity) : entity(entity) {

}

bool AiTaskWalkToPlayer::shouldExecute() {
    return true;
}

bool AiTaskWalkToPlayer::shouldContinueExecuting() {
    return abs(Global::player->pos.x - entity->pos.x) > entity->sprite.scale.x / 4;
}

void AiTaskWalkToPlayer::startExecuting() {
    entity->sprite.stateMachine.changeState(2); //TODO
}

void AiTaskWalkToPlayer::resetTask() {
    entity->sprite.stateMachine.changeState(0); //TODO
}

void AiTaskWalkToPlayer::updateTask(float deltaTime) {
    float direction = Global::player->pos.x > entity->pos.x ? 1.0 : -1.0;
    entity->pos += glm::vec2{direction * entity->speedModifier * deltaTime, 0};
    entity->sprite.invertTex = direction > 0;
}
