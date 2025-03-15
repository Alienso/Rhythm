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

    collisionBB = {(pos.x - 0.8333f * sprite.scale.x) / Configuration::aspectRatio, pos.y - 1.0f * sprite.scale.y,
                   (pos.x - 0.0833f * sprite.scale.x) / Configuration::aspectRatio, pos.y + 0.4167f * sprite.scale.y}; //TODO

    speedModifier = 0.5f;

    collisionSprite.scale = { collisionBB.maxX - collisionBB.minX, collisionBB.maxY - collisionBB.minY };
    collisionSprite.translate = { collisionSprite.scale.x / 2, collisionSprite.scale.y / 2 };

    aiTasks.push_back(new AiTaskWalkToPlayer(this));
}

Nightmare::~Nightmare() = default;
