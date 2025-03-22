//
// Created by Alienson on 22.3.2025..
//

#include "PistolWeapon.h"
#include "reference/Global.h"
#include "physics/RayTrace.h"

PistolWeapon::PistolWeapon() : RangedWeaponBase(Textures::PISTOL) {
    sprite.scale = {0.025, 0.025};
    mist.sprite.scale = {0.05, 0.05};
    mist.sprite.stateMachine = SpriteStateMachine(1, 15);
    mist.sprite.stateMachine.setTexturesCount({15});
    mist.sprite.stateMachine.animationSpeed = 1.2f;
}

void PistolWeapon::onRender() const {
    mist.onRender();
    RangedWeaponBase::onRender();
}

void PistolWeapon::onUpdate(float deltaTime, glm::vec2 &playerPos) {
    RangedWeaponBase::onUpdate(deltaTime, playerPos);
    mist.sprite.translate = sprite.translate;
}

void PistolWeapon::onAttack(BeatOffset* beatOffset) { //TODO try make this more generic and put some common code in base class

    attackCD = baseAttackCD;

    if (beatOffset == BeatOffset::MISS) {
        Global::soundEngine->play(Sounds::BEAT_MISS);
        Global::soundEngine->play(Sounds::REVOLVER_SHOOT_WEAK, soundStrength * 0.25f);
    } else {
        Global::soundEngine->play(Sounds::REVOLVER_SHOOT_WEAK, soundStrength);
    }

    RayTraceResult rayTraceResult = RayTracer::rayTrace(sprite.translate, Global::cursor->translate);

    auto trans = Particles::REVOLVER_SHOOT->getDefaultTransformations();
    if (rayTraceResult.hitType != HIT_TYPE_MISS){
        glm::vec2 offset = {(rayTraceResult.hitPoint.x - sprite.translate.x) / 2.0f, (rayTraceResult.hitPoint.y - sprite.translate.y) / 2.0};
        trans.scale = {0.05, rayTraceResult.distance / 2.0};
        trans.translation = sprite.translate + offset;
        trans.rotation = sprite.rotation - (float) M_PI / 2.0f;
    } else {
        trans.translation = {sprite.translate.x, sprite.translate.y}; //TODO
        trans.rotation = sprite.rotation - (float) M_PI / 2.0f;
        trans.scale = {0.05, 2.0};
    }

    Global::particleManager->spawnParticle(Particles::REVOLVER_SHOOT, trans);

    if (rayTraceResult.hitType == HIT_TYPE_ENTITY) {
        rayTraceResult.entityHit->damage(damage, beatOffset);
        Global::player->increaseComboPoints(comboPointsIncrease * beatOffset->comboMultiplier);
    }
}