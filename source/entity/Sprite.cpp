//
// Created by Alienson on 3.8.2024..
//

#include "Sprite.h"
#include "render/Shader.h"
#include "reference/Reference.h"
#include "Entity.h"
#include "glad.h"
#include "GLFW/glfw3.h"

Sprite::Sprite(Texture* tex) : texture(tex) {

}

Sprite::Sprite(Texture *texture, unsigned int animationStates) : texture(texture) {
    stateMachine = SpriteStateMachine(1, animationStates);
    stateMachine.setTexturesCount({animationStates});
}


Texture *Sprite::getTexture() const {
    return texture;
}

void Sprite::bind() const {
    getTexture()->bind(0);
    glBufferWrapper.va->bind();
}

void Sprite::onRender() const {
    Shader* shader = Shaders::SPRITE;
    shader->use();
    bind();
    shader->setInt("texture1", 0);
    if (parent != nullptr)
        shader->setVec2("translation", translate + parent->pos);
    else shader->setVec2("translation", translate);
    shader->setFloat("rotation", rotation);
    shader->setVec2("scale", scale);
    shader->setUInt("column", stateMachine.getAnimationState());
    shader->setUInt("columnMax", stateMachine.getTextureWidth());
    shader->setUInt("row", stateMachine.getState());
    shader->setUInt("rowMax", stateMachine.getStateCount());
    shader->setBool("invertTex", invertTex);
    shader->setFloat("time", (float)glfwGetTime());

    glDrawArrays(GL_TRIANGLES, 0, 6);
}