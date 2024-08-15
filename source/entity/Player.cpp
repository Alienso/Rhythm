//
// Created by Alienson on 10.8.2024..
//

#include "Player.h"
#include "reference/Global.h"

Player::Player(Texture *texture) : Entity(texture) {
    weapon.scale = {0.025, 0.025};
    mist.scale = {0.05, 0.05};
    mist.stateMachine = SpriteStateMachine(1, 15);
    mist.stateMachine.setTexturesCount({15});
    mist.stateMachine.animationSpeed = 1.2f;
}

void Player::onUpdate(float deltaTime) {
    weapon.pos = {pos.x, pos.y + 0.1};
    mist.pos = weapon.pos;
    weapon.rotation = atan2((Global::cursor->pos.y - weapon.pos.y), (Global::cursor->pos.x - weapon.pos.x));

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
    glm::vec2 normalizedWeaponDirection = glm::normalize(glm::vec2(Global::cursor->pos.x - weapon.pos.x, Global::cursor->pos.y - weapon.pos.y));
    trans.translation = { weapon.pos.x + normalizedWeaponDirection.x / 8.0, weapon.pos.y + normalizedWeaponDirection.y / 8.0 };
    trans.rotation = weapon.rotation + M_PI/4.0;
    Global::particleManager->spawnParticle(Particles::REVOLVER_SHOOT, trans);
}
