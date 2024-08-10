//
// Created by Alienson on 3.8.2024..
//

#include "Sprite.h"
#include "render/Shader.h"
#include "Assets.h"
#include "glad.h"

Sprite::Sprite(Texture* tex) : texture(tex) {

}

Texture *Sprite::getTexture() const {
    return texture;
}

void Sprite::bind() const {
    getTexture()->bind(0);
    glBufferWrapper.va->bind();
}

void Sprite::onRender() const {
    Shader *shader = Shaders::SPRITE;
    shader->use();
    bind();
    shader->setInt("texture1", 0);
    shader->setVec2("translation", pos);
    shader->setFloat("rotation", rotation);
    shader->setVec2("scale", scale);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
