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
    void spawnParticle(Particle* particle, AffineTransformations& trans, float lifetime = 0.0);

    void onUpdate(float deltaTime);
    void onRender();

private:
    std::vector<ParticleInstance> particles; //TODO maybe have 2 vectors for alive and dead? //TODO reallocaiton of this vector leads to destruction of GlBufferWrappers
};


#endif //RHYTHM_PARTICLEMANAGER_H
