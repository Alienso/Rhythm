//
// Created by Alienson on 22.3.2025..
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

void WeaponBase::onRender() const {
    sprite.onRender();
}

bool WeaponBase::canAttack() const {
    return attackCD <= 0;
}
