//
// Created by Alienson on 22.3.2025..
//

#ifndef RHYTHM_WEAPONBASE_H
#define RHYTHM_WEAPONBASE_H


#include <glm/vec2.hpp>
#include "sound/Sound.h"
#include "render/sprite/Sprite.h"
#include "sound/BeatOffset.h"
#include "physics/RayTrace.h"

class WeaponBase {
public:
    virtual ~WeaponBase();

    virtual void onUpdate(float deltaTime, glm::vec2& playerPos);
    virtual void onRender() const;
    virtual RayTraceResult onAttack(BeatOffset* beatOffset);

    [[nodiscard]] virtual Sound* getShootSound() const = 0;
    [[nodiscard]] bool canAttack() const;

protected:
    explicit WeaponBase(Texture* texture);

    float attackCD = 0.0;
    float baseAttackCD = 0.2f;
    float comboPointsIncrease = 20.0f;
    int damage = 1;
    float soundStrength = 0.6f;

    Sprite sprite;

};


#endif //RHYTHM_WEAPONBASE_H
