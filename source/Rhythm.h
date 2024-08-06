//
// Created by Alienson on 1.8.2024..
//

#ifndef RHYTHM_RHYTHM_H
#define RHYTHM_RHYTHM_H

#include "World.h"
#include "InputHandler.h"
#include "AssetManager.h"
#include "render/Texture.h"
#include "render/Shader.h"

class GLFWwindow;

class Rhythm {
public:
    Rhythm() = default;
    void run();

private:
    void init();
    void mainLoop();
    void cleanup();

    void initGlfw();
    void initImGui();
    void initAssets();

    void renderImGui();

    bool shouldContinue = true;
    double lastTime = 0;

    World* world = nullptr;
    InputHandler* inputHandler = nullptr;
    GLFWwindow* window = nullptr;
    AssetManager<Texture> textureManager;
    AssetManager<Shader> shaderManager;

};


#endif //RHYTHM_RHYTHM_H
