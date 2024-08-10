//
// Created by Alienson on 3.8.2024..
//

#include "Sprite.h"

Sprite::Sprite(Texture* tex) : texture(tex) {

}

Texture *Sprite::getTexture() const {
    return texture;
}

void Sprite::bind() const {
    getTexture()->bind(0);
    glBufferWrapper.va->bind();
}
