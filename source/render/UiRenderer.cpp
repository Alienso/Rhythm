//
// Created by Alienson on 10.8.2024..
//

#include "UiRenderer.h"
#include "Shader.h"
#include "glad.h"

UiRenderer::UiRenderer() {
    cursor.scale = {0.025,0.025};
}

void UiRenderer::onRender() {
    //draw Mouse
    Shader *shader = Shaders::SPRITE;
    shader->use();

    cursor.bind();
    shader->setInt("texture1", 0);
    shader->setVec2("translation", cursor.pos);
    shader->setFloat("rotation", cursor.rotation);
    shader->setVec2("scale", cursor.scale);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Sprite &UiRenderer::getCursor() {
    return cursor;
}
