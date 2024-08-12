//
// Created by Alienson on 3.8.2024..
//

#include "AssetManager.h"

#ifndef RHYTHM_ASSETS_H
#define RHYTHM_ASSETS_H

#include "render/Texture.h"
#include "render/Shader.h"
#include "sound/Sound.h"

class Textures{
public:
    static inline Texture* BLANK;
    static inline Texture* BACKGROUND;
    static inline Texture* BIKER;
    static inline Texture* CURSOR;
    static inline Texture* PISTOL;
    static inline Texture* MIST;
};

class Shaders{
public:
    static inline Shader* ENTITY;
    static inline Shader* SPRITE;
    static inline Shader* TEXTURE;
    static inline Shader* TEXTURE_MONO;
};

class Sounds{
public:
    static inline Sound* MTYN;
    static inline Sound* REVOLVER_SHOOT;
    static inline Sound* REVOLVER_SHOOT_WEAK;
    static inline Sound* SLASH_1;
};

#endif //RHYTHM_ASSETS_H