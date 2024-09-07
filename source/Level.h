//
// Created by Alienson on 1.8.2024..
//

#ifndef RHYTHM_LEVEL_H
#define RHYTHM_LEVEL_H


#include "entity/Sprite.h"
#include "reference/Reference.h"
#include "render/ParallaxTexture.h"
#include "entity/SpriteInstanced.h"

class Level {
public:
    Level();

    void onRender();
    void onUpdate(float deltaTime);

    static inline int score = 0;
private:
    SpriteInstanced spriteInstanced;
    ParallaxTexture background{ {"resource/texture/background/ParallaxMountain/sky.png",
                                 "resource/texture/background/ParallaxMountain/far-clouds.png",
                                 "resource/texture/background/ParallaxMountain/near-clouds.png",
                                 "resource/texture/background/ParallaxMountain/far-mountains.png",
                                 "resource/texture/background/ParallaxMountain/mountains.png",
                                 "resource/texture/background/ParallaxMountain/trees.png"},
                                {0.1f, 0.3f, 0.5f, 0.6f, 0.6f, 1.0f} };
};


#endif //RHYTHM_LEVEL_H
