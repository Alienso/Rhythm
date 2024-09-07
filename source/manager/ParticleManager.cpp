//
// Created by Alienson on 13.8.2024..
//

#include "ParticleManager.h"
#include "reference/Global.h"

ParticleManager::ParticleManager() {
    Global::particleManager = this;
    particles.reserve(100);
}

void ParticleManager::spawnParticle(Particle *particle, AffineTransformations& trans, float lifetime) { //TODO refactor

    bool spawned = false;
    for (ParticleInstance& p : particles){
        if (p.isDead()){
            p.revive(particle, trans, lifetime);
            spawned = true;
            break;
        }
    }
    if (!spawned){
        particles.emplace_back(particle, trans, lifetime);
    }
}

void ParticleManager::onUpdate(float deltaTime) {
    for (ParticleInstance& p : particles){
        if (!p.isDead())
            p.onUpdate(deltaTime);
    }
}

void ParticleManager::onRender() {
    for (ParticleInstance& p : particles){
        if (!p.isDead())
            p.onRender();
    }
}
