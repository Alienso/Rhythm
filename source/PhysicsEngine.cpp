//
// Created by Alienson on 10.8.2024..
//

#include "PhysicsEngine.h"
#include "Global.h"

PhysicsEngine::PhysicsEngine() {
    sprites.push_back(Global::player);
}

void PhysicsEngine::onUpdate(double deltaTime) {

    for (Sprite* sprite: sprites) {
        sprite->movementVec.y -= 9.81f * deltaTime;

        sprite->pos.x += sprite->movementVec.x * sprite->speedModifier * deltaTime;
        sprite->pos.y += sprite->movementVec.y * sprite->speedModifier * deltaTime;

        if (sprite->pos.y <= -0.9) {
            sprite->pos.y = -0.9;
            sprite->movementVec.y = 0;
            sprite->onGround = true;
        }

        if (sprite->pos.x > 1)
            sprite->pos.x = 1;
        if (sprite->pos.x < -1)
            sprite->pos.x = -1;



    }
}

void PhysicsEngine::registerSprite(Sprite *sprite) {
 sprites.push_back(sprite);
}
