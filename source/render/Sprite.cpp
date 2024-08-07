//
// Created by Alienson on 3.8.2024..
//

#include "Sprite.h"

Sprite::Sprite(Texture* tex, unsigned int states, unsigned int stages) :maxStates(states), maxAnimationStages(stages), texture(tex) {

}

Texture *Sprite::getTexture() const {
    return texture;
}

void Sprite::bind() const {
    getTexture()->bind(0);
    glBufferWrapper.va->bind();
}
