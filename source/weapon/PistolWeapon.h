//
// Created by Alienson on 22.3.2025..
//

#ifndef RHYTHM_PISTOLWEAPON_H
#define RHYTHM_PISTOLWEAPON_H


#include "RangedWeaponBase.h"
#include "entity/Sprite.h"
#include "reference/Reference.h"
#include "entity/Entity.h"

class PistolWeapon : public RangedWeaponBase {
public:
    PistolWeapon();
    void onAttack(BeatOffset* beatOffset) override;

    void onRender() const override;
    void onUpdate(float deltaTime, glm::vec2 &playerPos) override;

private:
    Entity mist{Textures::MIST};
};


#endif //RHYTHM_PISTOLWEAPON_H
