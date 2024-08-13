//
// Created by Alienson on 13.8.2024..
//

#include "Particle.h"

Particle::Particle(Texture *texture, float lifeTime) : Sprite(texture), lifetime(lifeTime){

}

ParticleInstance::ParticleInstance(Particle *particle, float lifeTime) : particle(particle) {
    if (lifeTime > 0)
        this->lifetime = lifeTime;
    else this->lifetime = particle->lifetime;
}

void ParticleInstance::revive(Particle *particle, float lifeTime) {
    this->particle = particle;
    if (lifeTime > 0) {
        this->lifetime = lifeTime;
    }else
        this->lifetime = particle->lifetime;
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

void ParticleInstance::onRender() {
    particle->onRender();
}
