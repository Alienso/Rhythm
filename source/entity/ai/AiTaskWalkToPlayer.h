//
// Created by Alienson on 24.8.2024..
//

#ifndef RHYTHM_AITASKWALKTOPLAYER_H
#define RHYTHM_AITASKWALKTOPLAYER_H


#include "AiTaskBase.h"
#include "entity/EntityLiving.h"

class AiTaskWalkToPlayer : public AiTaskBase {

public:
    explicit AiTaskWalkToPlayer(EntityLiving* entity);

    bool shouldExecute() override;
    bool shouldContinueExecuting() override;
    void startExecuting() override;
    void updateTask(float deltaTime) override;

    void resetTask() override;

private:
    EntityLiving* entity;
};


#endif //RHYTHM_AITASKWALKTOPLAYER_H
