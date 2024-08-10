//
// Created by Alienson on 1.8.2024..
//

#include "World.h"
#include "Assets.h"
#include "render/Shader.h"
#include "glad.h"
#include "GLFW/glfw3.h"
#include "Global.h"
#include "imgui/imgui.h"

World::World() {

}

void World::onRender() {

    Shader* shader = Shaders::TEXTURE;
    shader->use();

    //Draw background
    background.va->bind();
    Textures::BACKGROUND->bind(0);
    shader->setInt("texture1", 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Draw player
    shader = Shaders::BASE;
    shader->use();

    Global::player->bind();

    SpriteStateMachine& anim = Global::player->stateMachine;

    shader->setInt("texture1", 0);
    shader->setVec2("translation", Global::player->pos);
    shader->setFloat("rotation", Global::player->rotation);
    shader->setVec2("scale", Global::player->scale);
    shader->setUInt("column", anim.getAnimationState());
    shader->setUInt("columnMax", anim.getTextureWidth());
    shader->setUInt("row", anim.getState());
    shader->setUInt("rowMax", anim.getStateCount());
    shader->setFloat("time", (float)glfwGetTime());

    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void World::onUpdate(double deltaTime) {

}

void World::onImGuiRender() {
    ImGui::Begin("Hello, world!");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::SliderInt("State", (int*)&Global::player->stateMachine.state, 0, 10);
    ImGui::SliderFloat("AnimationSpeed", (float*)&Global::player->stateMachine.animationSpeed, 0, 1);

    ImGui::End();
}

void World::handleCollision() {

}
