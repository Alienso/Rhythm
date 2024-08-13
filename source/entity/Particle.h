//
// Created by Alienson on 13.8.2024..
//

#ifndef RHYTHM_PARTICLE_H
#define RHYTHM_PARTICLE_H

#include "Sprite.h"

class ParticleInstance;

class Particle : public Sprite{
public:
    explicit Particle(Texture* texture, float lifetime = 0.0);

    friend ParticleInstance;
private:
    float lifetime;
};

class ParticleInstance{
public:
    explicit ParticleInstance(Particle* particle, glm::vec2 pos, float lifeTime = 0.0);
    void revive(Particle* particle, glm::vec2 pos, float lifeTime = 0); //TODO maybe not allow different particle type

    void onUpdate(float deltaTime);
    void onRender();

    [[nodiscard]] bool isDead() const;
    [[nodiscard]] float getRemainingLife() const;

private:
    Particle* particle = nullptr;
    float lifetime;
};


#endif //RHYTHM_PARTICLE_H
