//
// Created by Alienson on 1.8.2024..
//

#include "World.h"
#include "Assets.h"
#include "render/Shader.h"
#include "glad.h"
#include "GLFW/glfw3.h"
#include "Global.h"

World::World() {

}

void World::onRender() {

    Shader* shader = Shaders::BASE;
    shader->use();

    //Draw background
    background.va->bind();
    Textures::BACKGROUND->bind(0);
    shader->setInt("texture1", 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Draw player
    Global::player->bind();
    shader->setInt("texture1", 0);
    shader->setVec2("translation", Global::player->translation);
    shader->setFloat("rotation", Global::player->rotation);
    shader->setVec2("scale", Global::player->scale);
    //shader->setFloat("uTime", (float)glfwGetTime());

    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void World::onUpdate(double deltaTime) {

}

void World::onImGuiRender() {

}

void World::handleCollision() {

}
