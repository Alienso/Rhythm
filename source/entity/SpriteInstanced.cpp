//
// Created by Alienson on 6.9.2024..
//

#include "SpriteInstanced.h"
#include "render/Shader.h"
#include "reference/Reference.h"
#include "render/buffer/GlBufferWrapperInstanced.h"

SpriteInstanced::SpriteInstanced() {

}

void SpriteInstanced::initialize(Texture *texture, std::vector<glm::fvec2>& offsets, glm::vec2 scale){
    this->texture = texture;
    glBufferWrapperInstanced.initialize(offsets, scale);
    this->instanceCount = (int)offsets.size();
}

void SpriteInstanced::onRender() const {
    Shader* shader = Shaders::SPRITE_INSTANCED;
    shader->use();

    texture->bind(0);
    glBufferWrapperInstanced.va.bind();

    shader->setInt("texture1", 0);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, instanceCount);
}

Texture *SpriteInstanced::getTexture() const {
    return texture;
}
