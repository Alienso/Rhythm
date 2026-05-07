//
// Created by Alienso on 22.3.2025.
//

#ifndef RHYTHM_PISTOLWEAPON_H
#define RHYTHM_PISTOLWEAPON_H


#include "WeaponBase.h"
#include "render/sprite/Sprite.h"
#include "reference/Reference.h"
#include "entity/Entity.h"

class PistolWeapon : public WeaponBase {
public:
    PistolWeapon();
    ~PistolWeapon() override;

    RayTraceResult onAttack(BeatOffsetType* beatOffset) override;

    void onRender() const override;
    void onUpdate(float deltaTime, glm::vec2 &playerPos) override;

    [[nodiscard]] Sound* getShootSound() const override;

private:
    Entity mist{Textures::MIST};
};


#endif //RHYTHM_PISTOLWEAPON_H
