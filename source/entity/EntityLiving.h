//
// Created by Alienson on 24.8.2024..
//

#ifndef RHYTHM_ENTITYLIVING_H
#define RHYTHM_ENTITYLIVING_H


#include "Entity.h"
#include "entity/ai/AiTaskBase.h"
#include "SpriteStates.h"

#include <array>

class EntityLiving : public Entity{

public:
    explicit EntityLiving(Texture *texture);
    ~EntityLiving() override;

    void onUpdate(float deltaTime) override;
    void damage(int amount);

    bool isAlive = true;
    float speedModifier = 1.0f; //TODO move
protected:
    std::vector<AiTaskBase*> aiTasks;
    AiTaskBase* currentTask = nullptr;
    int commonStates[STATE_COUNT] = {0,0};
    int health = 20;
    float invincibilityTime = 0;

protected:
    void updateAiTasks(float deltaTime);

};


#endif //RHYTHM_ENTITYLIVING_H
