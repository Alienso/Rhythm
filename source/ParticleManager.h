//
// Created by Alienson on 13.8.2024..
//

#ifndef RHYTHM_PARTICLEMANAGER_H
#define RHYTHM_PARTICLEMANAGER_H


#include <vector>
#include "entity/Particle.h"

class ParticleManager {
public:
    ParticleManager();
    void spawnParticle(Particle* particle, glm::vec2 pos, float lifetime = 0.0);

    void onUpdate(float deltaTime);
    void onRender();

private:
    std::vector<ParticleInstance> particles; //TODO maybe have 2 vectors for alive and dead?
};


#endif //RHYTHM_PARTICLEMANAGER_H
