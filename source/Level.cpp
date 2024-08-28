//
// Created by Alienson on 1.8.2024..
//

#include "Level.h"
#include "reference/Reference.h"
#include "render/Shader.h"
#include "glad.h"

Level::Level() {
}

void Level::onRender() {
    Shader* shader = Shaders::TEXTURE;
    shader->use();

    //Draw background
    background.va->bind();
    Textures::BACKGROUND->bind(0);
    shader->setInt("texture1", 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Level::onUpdate(float deltaTime) {

}
