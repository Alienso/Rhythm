//
// Created by Alienson on 24.8.2024..
//

#include "EntityLiving.h"

EntityLiving::EntityLiving(Texture *texture) : Entity(texture) {}

EntityLiving::~EntityLiving() {
    for (auto& task: aiTasks){
        delete task;
    }
}

void EntityLiving::onUpdate(float deltaTime) {

    pos.x += movementVec.x * speedModifier * deltaTime;
    pos.y += movementVec.y * deltaTime;

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
