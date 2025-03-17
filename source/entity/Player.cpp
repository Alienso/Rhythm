//
// Created by Alienson on 10.8.2024..
//

#include "Player.h"
#include "reference/Global.h"

#include <cmath>

Player::Player() : EntityLiving(Textures::BIKER) {

    Global::physicsEngine->registerEntity(this);
    Global::player = this;
    speedModifier = 1.2f;

    sprite.scale = glm::vec2(0.1, 0.1);
    sprite.stateMachine = *SpriteStateMachine(9, 8)
            .addTransitionsForState(0, {})
            ->addTransitionsForState(1, {})
            ->addTransitionsForState(2, {})
            ->addTransitionsForState(3, {})
            ->addTransitionsForState(4, {})
            ->addTransitionsForState(5, {})
            ->addTransitionsForState(6, {})
            ->addTransitionsForState(7, {})
            ->addTransitionsForState(8, {});
    sprite.stateMachine.setTexturesCount({6, 8, 6, 4, 6, 2, 4, 6, 6});

    collisionBB = {(pos.x - 0.4533f * sprite.scale.x), pos.y - 1.0f * sprite.scale.y,
                   (pos.x + 0.4533f * sprite.scale.x), pos.y + 0.4167f * sprite.scale.y};

    weapon.scale = {0.025, 0.025};
    mist.sprite.scale = {0.05, 0.05};
    mist.sprite.stateMachine = SpriteStateMachine(1, 15);
    mist.sprite.stateMachine.setTexturesCount({15});
    mist.sprite.stateMachine.animationSpeed = 1.2f;

    collisionSprite.scale = { (collisionBB.maxX - collisionBB.minX) / 2.0f, (collisionBB.maxY - collisionBB.minY) / 2.0f };
    collisionSprite.translate = { (collisionBB.maxX + collisionBB.minX) / 2.0f, (collisionBB.maxY + collisionBB.minY) / 2.0f };

}

void Player::onUpdate(float deltaTime) {

    EntityLiving::onUpdate(deltaTime);

    weapon.translate = {pos.x, pos.y + 0.1};
    mist.pos = weapon.translate;
    weapon.rotation = std::atan2((Global::cursor->translate.y - weapon.translate.y), (Global::cursor->translate.x - weapon.translate.x));

    if (attackCD > 0){
        attackCD-=deltaTime;
    }
}

bool Player::canAttack() const {
    return attackCD <= 0.0;
}

void Player::attack() {
    attackCD = 0.2;

    Global::soundEngine->play(Sounds::REVOLVER_SHOOT_WEAK, 0.6);
    auto trans = Particles::REVOLVER_SHOOT->getDefaultTransformations();
    trans.translation = { weapon.translate.x, weapon.translate.y};
    trans.rotation = weapon.rotation - (float)M_PI/2.0f;
    trans.scale = {0.05, 2.0};
    Global::particleManager->spawnParticle(Particles::REVOLVER_SHOOT, trans);
}

void Player::onRender() const {
    Entity::onRender();
    mist.onRender();
    weapon.onRender();
}
