//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_PHYSICSENGINE_H
#define RHYTHM_PHYSICSENGINE_H


#include "render/Sprite.h"

class PhysicsEngine {

public:

    PhysicsEngine();
    void onUpdate(double deltaTime);
    void registerSprite(Sprite* sprite);

private:
    std::vector<Sprite*> sprites;
};


#endif //RHYTHM_PHYSICSENGINE_H
