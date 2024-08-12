//
// Created by Alienson on 1.8.2024..
//

#ifndef RHYTHM_WORLD_H
#define RHYTHM_WORLD_H


#include "entity/Sprite.h"
#include "Assets.h"

class World {
public:
    World();

    void onRender();
    void onUpdate(float deltaTime);
    void onImGuiRender();

private:
    GlBufferWrapper background{quadVertices, sizeof(quadVertices) / sizeof(float)};
};


#endif //RHYTHM_WORLD_H
