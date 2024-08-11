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
#include "PhysicsEngine.h"
#include "render/UiRenderer.h"
#include "sound/Sound.h"
#include "sound/SoundEngine.h"

class GLFWwindow;

class Rhythm {
public:
    Rhythm() = default;
    void run();

    friend InputHandler;

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
    PhysicsEngine* physicsEngine = nullptr;
    SoundEngine* soundEngine = nullptr;
    UiRenderer* uiRenderer = nullptr;
    GLFWwindow* window = nullptr;
    AssetManager<Texture> textureManager;
    AssetManager<Shader> shaderManager;
    AssetManager<Sound> soundManager;

};


#endif //RHYTHM_RHYTHM_H
