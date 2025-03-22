//
// Created by Alienson on 24.8.2024..
//

#include "EntityLiving.h"
#include "SpriteStates.h"
#include "reference/Global.h"
#include "Level.h"

EntityLiving::EntityLiving(Texture *texture) : Entity(texture) {}

EntityLiving::~EntityLiving() {
    for (auto& task: aiTasks){
        delete task;
    }
}

void EntityLiving::onUpdate(float deltaTime) {

    if (!isAlive)
        return;

    invincibilityTime-=deltaTime;
    if (invincibilityTime < 0)
        invincibilityTime = 0;

    collisionBB.translate(pos - previousPos); //TODO if entity is rotated x offset needs to change

    previousPos = pos;
    pos.x += movementVec.x * speedModifier * deltaTime;
    pos.y += movementVec.y * deltaTime;

    updateAiTasks(deltaTime);
}

void EntityLiving::updateAiTasks(float deltaTime) {

    if (aiTasks.empty())
        return;

    //TODO interruptible
    if (currentTask == nullptr) {
        for (AiTaskBase* task: aiTasks) {
            if (task->shouldExecute()){
                currentTask = task;
                currentTask->startExecuting();
            }
        }
    }

    if (currentTask->shouldContinueExecuting()){
        currentTask->updateTask(deltaTime);
    }else{
        currentTask->resetTask();
        currentTask = nullptr;
    }
}

void EntityLiving::damage(int amount, BeatOffset* beatOffset) {

    if (invincibilityTime > 0)
        return;

    health -= amount * Global::player->getRhythmMultiplier()->damage * beatOffset->damageMultiplier;
    sprite.stateMachine.changeState(commonStates[STATE_HURT]);
    invincibilityTime = 0.5f;
    if (health <= 0) {
        if (isAlive){
            sprite.stateMachine.changeState(STATE_DEATH);
            Global::entityManger->scheduleDeSpawn(this);
            Level::increaseScore(scoreValue, beatOffset->scoreMultiplier);
        }
        health = 0;
        isAlive = false;
    }
}
