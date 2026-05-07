//
// Created by Alienson on 24.8.2024..
//

#ifndef RHYTHM_ENTITYLIVING_H
#define RHYTHM_ENTITYLIVING_H


#include "Entity.h"
#include "entity/ai/AiTaskBase.h"
#include "render/sprite/SpriteStates.h"
#include "sound/BeatOffsetType.h"

#include <array>

class EntityLiving : public Entity {

public:
    explicit EntityLiving(Texture *texture);
    ~EntityLiving() override;

    void onUpdate(float deltaTime) override;
    void damage(int amount, BeatOffsetType* beatOffset); //TODO maybe use global object for this beatOffset?

    bool isAlive = true;
protected:
    std::vector<AiTaskBase*> aiTasks;
    AiTaskBase* currentTask = nullptr;
    unsigned int commonStates[STATE_COUNT] = {0,0};
    int health = 20;
    unsigned int scoreValue = 200;
    float invincibilityTime = 0;

protected:
    void updateAiTasks(float deltaTime);

};


#endif //RHYTHM_ENTITYLIVING_H
