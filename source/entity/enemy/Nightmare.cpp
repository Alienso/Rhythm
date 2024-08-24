//
// Created by Alienson on 22.8.2024..
//

#include "Nightmare.h"
#include "reference/Reference.h"
#include "reference/Global.h"
#include "entity/ai/AiTaskWalkToPlayer.h"

Nightmare::Nightmare() : EntityLiving(Textures::NIGHTMARE) {
    Global::physicsEngine->registerEntity(this);

    sprite.scale = glm::vec2(0.3,0.2);
    sprite.stateMachine = SpriteStateMachine(3, 4);
    sprite.stateMachine.setTexturesCount({4,4,4});
    sprite.stateMachine.animationSpeed = 0.7f;
    sprite.stateMachine.changeState(0);

    speedModifier = 0.5f;

    aiTasks.push_back(new AiTaskWalkToPlayer(this));
}

Nightmare::~Nightmare() = default;
