//
// Created by Alienson on 22.3.2025.
//

#include "PistolWeapon.h"
#include "reference/Global.h"
#include "physics/RayTrace.h"

PistolWeapon::PistolWeapon() : WeaponBase(Textures::PISTOL) {
    sprite.scale = {0.025, 0.025};
    mist.sprite.scale = {0.05, 0.05};
    mist.sprite.stateMachine = SpriteStateMachine(1, 15);
    mist.sprite.stateMachine.setTexturesCount({15});
    mist.sprite.stateMachine.animationSpeed = 1.2f;

    damage = 10;
}

PistolWeapon::~PistolWeapon() {

}

void PistolWeapon::onRender() const {
    mist.onRender();
    WeaponBase::onRender();
}

void PistolWeapon::onUpdate(float deltaTime, glm::vec2 &playerPos) {
    WeaponBase::onUpdate(deltaTime, playerPos);
    mist.sprite.translate = sprite.translate;
}

RayTraceResult PistolWeapon::onAttack(BeatOffset* beatOffset) {

    RayTraceResult rayTraceResult = WeaponBase::onAttack(beatOffset);

    auto trans = Particles::REVOLVER_SHOOT->getDefaultTransformations();
    if (rayTraceResult.hitType != HIT_TYPE_MISS){
        glm::vec2 offset = {(rayTraceResult.hitPoint.x - sprite.translate.x) / 2.0f,
                            (rayTraceResult.hitPoint.y - sprite.translate.y) / 2.0};
        trans.scale = {0.05, rayTraceResult.distance / 2.0};
        trans.translation = sprite.translate + offset;
        trans.rotation = sprite.rotation - (float) glm::pi<float>() / 2.0f;
    } else {
        trans.translation = {sprite.translate.x, sprite.translate.y};
        trans.rotation = sprite.rotation - (float) glm::pi<float>() / 2.0f;
        trans.scale = {0.05, 2.0};
    }

    Global::particleManager->spawnParticle(Particles::REVOLVER_SHOOT, trans);

    return rayTraceResult;
}

Sound *PistolWeapon::getShootSound() const {
    return Sounds::BEAT;
}