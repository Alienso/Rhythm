//
// Created by Alienson on 10.8.2024..
//

#include "UiRenderer.h"
#include "Shader.h"
#include "glad.h"

UiRenderer::UiRenderer() {
    cursor.scale = {0.025,0.025};

    multiplierFrame.translate = {0.0, 0.8};
    multiplierFrame.scale = {0.15,0.15};

    multiplierFlame.translate= {0.0,0.8};
    multiplierFlame.scale = {0.2,0.2};
    multiplierFlame.stateMachine.animationSpeed = 1.05;
}

void UiRenderer::onRender() {
    //draw Mouse
    Shader *shader = Shaders::SPRITE_STATIC;
    shader->use();

    cursor.bind();
    shader->setInt("texture1", 0);
    shader->setVec2("translation", cursor.translate);
    shader->setFloat("rotation", cursor.rotation);
    shader->setVec2("scale", cursor.scale);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    multiplierFlame.onRender();

    shader->use();
    multiplierFrame.bind();
    shader->setInt("texture1", 0);
    shader->setVec2("translation", multiplierFrame.translate);
    shader->setFloat("rotation", multiplierFrame.rotation);
    shader->setVec2("scale", multiplierFrame.scale);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

Sprite &UiRenderer::getCursor() {
    return cursor;
}
