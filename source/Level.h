//
// Created by Alienson on 1.8.2024..
//

#ifndef RHYTHM_LEVEL_H
#define RHYTHM_LEVEL_H


#include "entity/Sprite.h"
#include "reference/Reference.h"

class Level {
public:
    Level();

    void onRender();
    void onUpdate(float deltaTime);

    static inline int score = 0;
private:
    GlBufferWrapper background{quadVertices, sizeof(quadVertices) / sizeof(float)};
};


#endif //RHYTHM_LEVEL_H
