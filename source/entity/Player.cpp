//
// Created by Alienson on 10.8.2024..
//

#include "Player.h"
#include "reference/Global.h"

Player::Player() : EntityLiving(Textures::BIKER) {

    Global::physicsEngine->registerEntity(this);
    Global::player = this;

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

    //glm::vec2 bbScale = {sprite.scale.x * 0.2916, sprite.scale.y * 0.7083};
    //glm::vec2 bbPosOffset = {pos.x - 0.4167 * bbScale.x, pos.y - 0.2917 * bbScale.y};
    collisionBB = {(pos.x - 0.8333f * sprite.scale.x) / Configuration::aspectRatio, pos.y - 1.0f * sprite.scale.y,
                   (pos.x - 0.0833f * sprite.scale.x) / Configuration::aspectRatio, pos.y + 0.4167f * sprite.scale.y};

    weapon.scale = {0.025, 0.025};
    mist.sprite.scale = {0.05, 0.05};
    mist.sprite.stateMachine = SpriteStateMachine(1, 15);
    mist.sprite.stateMachine.setTexturesCount({15});
    mist.sprite.stateMachine.animationSpeed = 1.2f;
}

void Player::onUpdate(float deltaTime) {

    EntityLiving::onUpdate(deltaTime);

    weapon.translate = {pos.x, pos.y + 0.1};
    mist.pos = weapon.translate;
    weapon.rotation = atan2((Global::cursor->translate.y - weapon.translate.y), (Global::cursor->translate.x - weapon.translate.x));

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
    glm::vec2 normalizedWeaponDirection = glm::normalize(glm::vec2(Global::cursor->translate.x - weapon.translate.x, Global::cursor->translate.y - weapon.translate.y));
    trans.translation = { weapon.translate.x + normalizedWeaponDirection.x / 8.0, weapon.translate.y + normalizedWeaponDirection.y / 8.0 };
    trans.rotation = weapon.rotation + M_PI/4.0;
    Global::particleManager->spawnParticle(Particles::REVOLVER_SHOOT, trans);
}

void Player::onRender() const {
    Entity::onRender();
    mist.onRender();
    weapon.onRender();
}
