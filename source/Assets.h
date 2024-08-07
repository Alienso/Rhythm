//
// Created by Alienson on 3.8.2024..
//

#include "AssetManager.h"

#ifndef RHYTHM_ASSETS_H
#define RHYTHM_ASSETS_H

#include "render/Texture.h"
#include "render/Shader.h"

class Textures{
public:
    static inline Texture* BLANK;
    static inline Texture* BACKGROUND;
    static inline Texture* BIKER;
};

class Shaders{
public:
    static inline Shader* BASE;
    static inline Shader* TEXTURE;
    static inline Shader* TEXTURE_MONO;
};

#endif //RHYTHM_ASSETS_H