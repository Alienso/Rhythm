//
// Created by Alienson on 24.8.2024..
//

#ifndef RHYTHM_ENTITYLIVING_H
#define RHYTHM_ENTITYLIVING_H


#include "Entity.h"
#include "entity/ai/AiTaskBase.h"

class EntityLiving : public Entity{

public:
    explicit EntityLiving(Texture *texture);
    ~EntityLiving() override;

    void onUpdate(float deltaTime) override;

    bool isAlive = true;
    float speedModifier = 1.0f;
protected:
    std::vector<AiTaskBase*> aiTasks;
    AiTaskBase* currentTask = nullptr;

protected:
    void updateAiTasks(float deltaTime);

};


#endif //RHYTHM_ENTITYLIVING_H
