//
// Created by Alienson on 13.8.2024..
//

#ifndef RHYTHM_PARTICLE_H
#define RHYTHM_PARTICLE_H

#include "Sprite.h"

class ParticleInstance;

class Particle{
public:
    explicit Particle(Texture* texture, unsigned int animationStates, AffineTransformations& transformations, float lifetime);

    [[nodiscard]] AffineTransformations getDefaultTransformations() const;

    friend ParticleInstance;
private:
    Texture* texture;
    AffineTransformations affineTransformations;
    unsigned int animationStates;
    float lifetime;

};

class ParticleInstance : public Sprite{
public:
    explicit ParticleInstance(Particle* particle, AffineTransformations& trans, float lifeTime = 0.0);
    void revive(Particle* particle, AffineTransformations& trans, float lifeTime = 0); //TODO maybe not allow different particle type

    void onUpdate(float deltaTime);

    [[nodiscard]] bool isDead() const;
    [[nodiscard]] float getRemainingLife() const;

private:
    Particle* particle = nullptr;
    float lifetime;
};


#endif //RHYTHM_PARTICLE_H
