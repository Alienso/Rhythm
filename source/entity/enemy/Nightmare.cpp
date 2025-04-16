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

    rebuildCollisionBoxes();

    speedModifier = 0.5f;

    collisionSprite.scale = { (collisionBB.maxX - collisionBB.minX) / 2.0f, (collisionBB.maxY - collisionBB.minY) / 2.0f };

    aiTasks.push_back(new AiTaskWalkToPlayer(this));
}

void Nightmare::rebuildCollisionBoxes() {
    collisionBB = {(pos_.x - 0.65f * sprite.scale.x), pos_.y - 1.0f * sprite.scale.y,
                   (pos_.x + 0.65f * sprite.scale.x), pos_.y + 0.4167f * sprite.scale.y};

    collisionSprite.translate = { (collisionBB.maxX + collisionBB.minX) / 2.0f, (collisionBB.maxY + collisionBB.minY) / 2.0f };
}

Nightmare::~Nightmare() = default;
