//
// Created by Alienson on 3.8.2024..
//

#include <iostream>
#include "Sprite.h"

Sprite::Sprite() {

}

void Sprite::addState(unsigned int state, Texture *texture) {
    if (textures.size() <= state)
        textures.resize(state + 1);
    textures[state] = texture;
}

Texture *Sprite::getTexture(unsigned int state) const {
    if (textures.size() <= state){
        std::cout << "No state " << state << " found in texture list";
        exit(1);
    }
    return textures[state];
}

void Sprite::bind() const {
    getTexture(state)->bind(0);
    glBufferWrapper.va->bind();
}
