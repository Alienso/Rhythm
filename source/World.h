//
// Created by Alienson on 1.8.2024..
//

#ifndef RHYTHM_WORLD_H
#define RHYTHM_WORLD_H


#include "render/Sprite.h"

class World {
public:
    World();

    void onRender();
    void onUpdate(double deltaTime);
    void onImGuiRender();

private:
    void handleCollision();

    GlBufferWrapper background{quadVertices, sizeof(quadVertices) / sizeof(float)};
};


#endif //RHYTHM_WORLD_H
