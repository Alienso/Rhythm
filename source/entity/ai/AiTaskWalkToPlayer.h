//
// Created by Alienson on 24.8.2024..
//

#ifndef RHYTHM_AITASKWALKTOPLAYER_H
#define RHYTHM_AITASKWALKTOPLAYER_H


#include "AiTaskBase.h"
#include "entity/Entity.h"

class AiTaskWalkToPlayer : public AiTaskBase {

public:
    explicit AiTaskWalkToPlayer(Entity* entity);

    bool shouldExecute() override;
    bool shouldContinueExecuting() override;
    void startExecuting() override;
    void updateTask() override;

private:
    Entity* entity;
};


#endif //RHYTHM_AITASKWALKTOPLAYER_H
