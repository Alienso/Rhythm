//
// Created by Alienson on 22.3.2025..
//

#ifndef RHYTHM_RANGEDWEAPONBASE_H
#define RHYTHM_RANGEDWEAPONBASE_H


#include <glm/vec2.hpp>
#include "sound/Sound.h"
#include "entity/Sprite.h"
#include "sound/BeatOffset.h"

class RangedWeaponBase {
public:
    virtual void onUpdate(float deltaTime, glm::vec2& playerPos);
    virtual void onRender() const;

    [[nodiscard]] bool canAttack() const;
    virtual void onAttack(BeatOffset* beatOffset) = 0;
protected:
    explicit RangedWeaponBase(Texture* texture);

    float attackCD = 0.0;
    float baseAttackCD = 0.2f;
    float comboPointsIncrease = 20.0f;
    float damage = 1.0f;
    float soundStrength = 0.6f;

    Sprite sprite;

};


#endif //RHYTHM_RANGEDWEAPONBASE_H
