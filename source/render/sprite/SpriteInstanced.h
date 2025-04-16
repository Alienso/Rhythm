//
// Created by Alienson on 6.9.2024..
//

#ifndef RHYTHM_SPRITEINSTANCED_H
#define RHYTHM_SPRITEINSTANCED_H


#include "render/Texture.h"
#include "render/buffer/GlBufferWrapper.h"
#include "Sprite.h"
#include "render/buffer/GlBufferWrapperInstanced.h"

class SpriteInstanced {
public:
    SpriteInstanced();
    void initialize(Texture *texture, std::vector<glm::fvec2>& offsets, glm::vec2 scale);
    [[nodiscard]] Texture* getTexture() const;

    void onRender() const;

private:
    Texture* texture = nullptr;
    GlBufferWrapperInstanced glBufferWrapperInstanced;
    int instanceCount;
};


#endif //RHYTHM_SPRITEINSTANCED_H
