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

    void onUpdate() override;

    bool isAlive = true;
protected:
    std::vector<AiTaskBase*> aiTasks;
    AiTaskBase* currentTask = nullptr;

};


#endif //RHYTHM_ENTITYLIVING_H
