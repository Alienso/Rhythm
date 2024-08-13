//
// Created by Alienson on 10.8.2024..
//

#include "Entity.h"
#include "render/Shader.h"
#include "reference/Reference.h"
#include "glad.h"
#include "GLFW/glfw3.h"

Entity::Entity(Texture *texture) : Sprite(texture) {

}

void Entity::onRender() const {
    Shader* shader = Shaders::ENTITY;
    shader->use();
    bind();
    shader->setInt("texture1", 0);
    shader->setVec2("translation", pos);
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
