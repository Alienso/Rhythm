//
// Created by Alienson on 22.3.2025.
//

#include "WeaponBase.h"
#include "reference/Global.h"

WeaponBase::WeaponBase(Texture *texture) : sprite(texture) {

}

WeaponBase::~WeaponBase() {

}

void WeaponBase::onUpdate(float deltaTime, glm::vec2& playerPos) {
    sprite.translate = {playerPos.x, playerPos.y + 0.1};
    sprite.rotation = std::atan2(Global::cursor->translate.y - (sprite.translate.y - Global::camera->getOffset().y),
                                 Global::cursor->translate.x - (sprite.translate.x - Global::camera->getOffset().x));

    if (attackCD > 0){
        attackCD-=deltaTime;
    }
}

RayTraceResult WeaponBase::onAttack(BeatOffset* beatOffset) {

    attackCD = baseAttackCD;

    //TODO update this so weapon is always heard, but when beat offset is miss, BEAT_MISS sound is also played
    if (beatOffset == BeatOffset::MISS) {
        //Global::soundEngine->play(Sounds::BEAT_MISS);
        Global::soundEngine->play(Sounds::REVOLVER_SHOOT_WEAK, soundStrength * 0.25f);
        Global::player->adjustComboPoints(-comboPointsIncrease);
    } else {
        Global::soundEngine->play(getShootSound(), soundStrength);
    }

    RayTraceResult rayTraceResult = RayTracer::rayTrace(sprite.translate, Global::cursor->translate + Global::camera->getOffset());

    if (rayTraceResult.hitType == HIT_TYPE_ENTITY) {
        rayTraceResult.entityHit->damage(damage, beatOffset);
        Global::player->adjustComboPoints(comboPointsIncrease * beatOffset->comboMultiplier);
    }

    return rayTraceResult;
}

void WeaponBase::onRender() const {
    sprite.onRender();
}

bool WeaponBase::canAttack() const {
    return attackCD <= 0;
}
