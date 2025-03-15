//
// Created by Alienson on 3.8.2024..
//

#include "manager/AssetManager.h"

#ifndef RHYTHM_ASSETS_H
#define RHYTHM_ASSETS_H

#include "render/Texture.h"
#include "render/Shader.h"
#include "sound/Sound.h"
#include "entity/Particle.h"

class Textures{
public:
    static inline Texture* BLANK;
    static inline Texture* BACKGROUND;
    static inline Texture* BIKER;
    static inline Texture* CURSOR;
    static inline Texture* PISTOL;
    static inline Texture* MIST;
    static inline Texture* MULTIPLIER_FRAME;
    static inline Texture* FLAME_CIRCLE;
    static inline Texture* PARTICLE_GUNSHOT;
    static inline Texture* NIGHTMARE;
    static inline Texture* COLLISION_BOX;
};

class Shaders{
public:
    static inline Shader* SPRITE;
    static inline Shader* SPRITE_STATIC;
    static inline Shader* SPRITE_INSTANCED;
    static inline Shader* TEXTURE;
    static inline Shader* TEXTURE_MONO;
    static inline Shader* TEXTURE_PARALLAX;
};

class Sounds{
public:
    static inline Sound* MTYN;
    static inline Sound* DISSOLUTION;
    static inline Sound* DEVASTATION;
    static inline Sound* REVOLVER_SHOOT;
    static inline Sound* REVOLVER_SHOOT_WEAK;
    static inline Sound* SLASH_1;
};

class Particles{
public:
    static inline Particle* REVOLVER_SHOOT;
};

#endif //RHYTHM_ASSETS_H