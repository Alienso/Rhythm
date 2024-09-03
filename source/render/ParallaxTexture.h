//
// Created by Alienson on 1.9.2024..
//

#ifndef RHYTHM_PARALLAXTEXTURE_H
#define RHYTHM_PARALLAXTEXTURE_H


#include "Texture.h"
#include "render/buffer/GlBufferWrapper.h"

class ParallaxTexture {
public:
    explicit ParallaxTexture(std::vector<const char*> paths, std::vector<float> speedModifiers);
    ~ParallaxTexture();

    void translate(float x);
    void onRender() const;

private:
    std::vector<Texture*> textures;
    std::vector<float> speedModifiers;
    std::vector<float> offsets;
    std::vector<float> aspectRatios;
    std::vector<GlBufferWrapper> glBuffers;
};


#endif //RHYTHM_PARALLAXTEXTURE_H
