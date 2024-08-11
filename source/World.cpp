//
// Created by Alienson on 1.8.2024..
//

#include "World.h"
#include "Assets.h"
#include "render/Shader.h"
#include "glad.h"
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
    Global::player->onRender();
    Global::player->mist.onRender();
    Global::player->weapon.onRender();

}

void World::onUpdate(double deltaTime) {
    Global::player->onUpdate();

}

void World::onImGuiRender() {
    ImGui::Begin("Hello, world!");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::SliderFloat("AnimationSpeed", (float*)&Global::player->stateMachine.animationSpeed, 0, 1);

    ImGui::End();
}
