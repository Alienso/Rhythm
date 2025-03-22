//
// Created by Alienson on 22.3.2025..
//

#include "RangedWeaponBase.h"
#include "reference/Global.h"

RangedWeaponBase::RangedWeaponBase(Texture *texture) : sprite(texture) {

}

void RangedWeaponBase::onUpdate(float deltaTime, glm::vec2& playerPos) {
    sprite.translate = {playerPos.x, playerPos.y + 0.1};
    sprite.rotation = std::atan2((Global::cursor->translate.y - sprite.translate.y), (Global::cursor->translate.x - sprite.translate.x));

    if (attackCD > 0){
        attackCD-=deltaTime;
    }
}

void RangedWeaponBase::onRender() const {
    sprite.onRender();
}

bool RangedWeaponBase::canAttack() const {
    return attackCD <= 0;
}
