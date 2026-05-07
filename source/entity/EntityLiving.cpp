//
// Created by Alienso on 24.8.2024.
//

#include "EntityLiving.h"
#include "render/sprite/SpriteStates.h"
#include "reference/Global.h"
#include "level/Level.h"

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
                break;
            }
        }
    }

    assert(currentTask != nullptr);

    if (currentTask->shouldContinueExecuting()){
        currentTask->updateTask(deltaTime);
    }else{
        currentTask->resetTask();
        currentTask = nullptr;
    }
}

void EntityLiving::damage(int amount, BeatOffsetType* beatOffset) {

    if (invincibilityTime > 0)
        return;

    health -= amount * Global::player->getCurrentRhythmMultiplier()->damageMultiplier * beatOffset->damageMultiplier;
    sprite.stateMachine.changeState(commonStates[STATE_HURT]);
    invincibilityTime = 0.5f;
    if (health <= 0) {
        if (isAlive){
            sprite.stateMachine.changeState(STATE_DEATH);
            Global::entityManger->scheduleDeSpawn(this, 0);
            Level::increaseScore(scoreValue, beatOffset->scoreMultiplier);
        }
        health = 0;
        isAlive = false;
    }
}
