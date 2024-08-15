//
// Created by Alienson on 13.8.2024..
//

#include "Particle.h"

Particle::Particle(Texture *texture, unsigned int animationStates, AffineTransformations &transformations, float lifeTime)
            : texture(texture), affineTransformations(transformations), animationStates(animationStates),lifetime(lifeTime) {

}

AffineTransformations Particle::getDefaultTransformations() const {
    return affineTransformations;
}

ParticleInstance::ParticleInstance(Particle *particle, AffineTransformations& trans, float lifeTime) : Sprite(particle->texture), particle(particle) {
    if (lifeTime > 0)
        this->lifetime = lifeTime;
    else this->lifetime = particle->lifetime;

    pos = trans.translation;
    rotation = trans.rotation;
    scale = trans.scale;

    stateMachine = SpriteStateMachine(1,particle->animationStates); //TODO depending on animation states and lifetime, increase or decrease animation speed
    stateMachine.setTexturesCount({particle->animationStates});
}

void ParticleInstance::revive(Particle *particle, AffineTransformations& trans, float lifeTime) { //TODO this will not work if Particle type changes
    this->particle = particle;
    if (lifeTime > 0) {
        this->lifetime = lifeTime;
    }else
        this->lifetime = particle->lifetime;

    pos = trans.translation;
    rotation = trans.rotation;
    scale = trans.scale;
}

void ParticleInstance::onUpdate(float deltaTime) {
    if (lifetime > 0)
        lifetime-=deltaTime;
}

bool ParticleInstance::isDead() const {
    return lifetime <=0;
}

float ParticleInstance::getRemainingLife() const {
    return lifetime;
}