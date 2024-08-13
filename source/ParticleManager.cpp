//
// Created by Alienson on 13.8.2024..
//

#include "ParticleManager.h"

ParticleManager::ParticleManager() {

}

void ParticleManager::spawnParticle(Particle *particle, glm::vec2 pos, float lifetime) { //TODO refactor

    bool spawned = false;
    for (ParticleInstance& p : particles){
        if (p.isDead()){
            p.revive(particle, pos, lifetime);
            spawned = true;
            break;
        }
    }
    if (!spawned){
        particles.emplace_back(particle, pos, lifetime);
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
