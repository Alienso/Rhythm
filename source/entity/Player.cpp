//
// Created by Alienson on 10.8.2024..
//

#include "Player.h"
#include "reference/Global.h"
#include "physics/RayTrace.h"

#include <cmath>

Player::Player() : EntityLiving(Textures::BIKER) {

    Global::physicsEngine->registerEntity(this);
    Global::player = this;
    speedModifier = 1.2f;

    sprite.scale = glm::vec2(0.1, 0.1);
    sprite.stateMachine = SpriteStateMachine(9, 8);
    sprite.stateMachine.setTexturesCount({6, 8, 6, 4, 6, 2, 4, 6, 6});
    commonStates[STATE_DEATH] = 2;
    commonStates[STATE_HURT] = 5;

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

    RayTraceResult rayTraceResult = RayTracer::rayTrace(weapon.translate, Global::cursor->translate);
    if (rayTraceResult.hitType != HIT_TYPE_MISS){
        glm::vec2 offset = {(rayTraceResult.hitPoint.x - weapon.translate.x) / 2.0f, (rayTraceResult.hitPoint.y - weapon.translate.y) / 2.0};
        trans.scale = {0.05, rayTraceResult.distance / 2.0};
        trans.translation = weapon.translate + offset;
        trans.rotation = weapon.rotation - (float) M_PI / 2.0f;
    } else {
        trans.translation = {weapon.translate.x, weapon.translate.y}; //TODO
        trans.rotation = weapon.rotation - (float) M_PI / 2.0f;
        trans.scale = {0.05, 2.0};
    }

    Global::particleManager->spawnParticle(Particles::REVOLVER_SHOOT, trans);

    if (rayTraceResult.hitType == HIT_TYPE_ENTITY){
        rayTraceResult.entityHit->damage(10);
    }
}

void Player::onRender() const {
    Entity::onRender();
    mist.onRender();
    weapon.onRender();
}
