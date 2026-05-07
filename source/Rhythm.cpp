//
// Created by Alienso on 1.8.2024.
//

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "Rhythm.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "reference/Configuration.h"
#include "InputHandler.h"
#include "reference/Global.h"
#include "sound/BeatOffsetType.h"
#include "manager/BeatManager.h"

#include <iostream>

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

}

void GLAPIENTRY glErrorCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ){
    if (type != GL_DEBUG_TYPE_ERROR)
        return;
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", "** GL ERROR **", type, severity, message );
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    Configuration::windowWidth = width;
    Configuration::windowHeight = height;
}

void Rhythm::initGlfw(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfwWindowHint(GLFW_SAMPLES, 4);

    //window = glfwCreateWindow(Configuration::windowWidth, Configuration::windowHeight, "Rhythm", glfwGetPrimaryMonitor(), nullptr);
    window = glfwCreateWindow(Configuration::windowWidth, Configuration::windowHeight, "Rhythm", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(0); //VSYNC

    GLFWimage images[1] = { GLFWimage{} };
    images[0].pixels = stbi_load("resource/icon.png", &images[0].width, &images[0].height, nullptr, 4); //rgba channels
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_MULTISAMPLE);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    auto aspectRatio = (float)((double)Configuration::windowHeight/(double)Configuration::windowWidth);
    float aspectFixMatrix[16] = {aspectRatio, 0, 0, 0, //GLSL aligns vec3 to vec4, so we have to add this extra zeros
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 0};
    unsigned int uboAspectFix;
    glGenBuffers(1, &uboAspectFix);
    glBindBuffer(GL_UNIFORM_BUFFER, uboAspectFix);
    glBufferData(GL_UNIFORM_BUFFER, 48, aspectFixMatrix, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboAspectFix);
}

void Rhythm::initImGui(){
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    ImGui::StyleColorsDark();
}

void Rhythm::renderImGui(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Hello, world!");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    //ImGui::SliderFloat("AnimationSpeed", (float*)&Global::player->stateMachine.animationSpeed, 0, 1);
    ImGui::Text("Score: %d", Level::score);
    ImGui::Text("Player Pos: %.2f %.2f", entityManager->player.pos().x, entityManager->player.pos().y);
    //ImGui::Text("Player BB: minX: %.2f, maxX: %.2f, minY: %.2f, maxY: %.2f", entityManager->player.collisionBB.minX, entityManager->player.collisionBB.maxX, entityManager->player.collisionBB.minY, entityManager->player.collisionBB.maxY);
    ImGui::Text("OnGround: %d", Global::player->onGround);

    if (ImGui::Button("Seek+"))
        soundEngine->seek(10);
    if (ImGui::Button("Seek-"))
        soundEngine->seek(-10);

    ImGui::Checkbox("Render collision boxes", &UiRenderer::showCollisionBoxes);

    ImGui::Text("ComboPoints: %f", Global::player->comboPoints);
    ImGui::Text("Multiplier: %i", Global::player->rhythmMultiplierIndex);
    ImGui::Text("BeatFrame: %.2f", BeatManager::getCurrentFrame().middle);

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Rhythm::run() {
    init();
    mainLoop();
    cleanup();
}

void Rhythm::init() {
    initGlfw();
    initImGui();

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( glErrorCallback, nullptr );
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    srand((unsigned int)glfwGetTime());

    initAssets();
    initWeapons();

    Global::init();

    inputHandler = new InputHandler(this);
    physicsEngine = new PhysicsEngine();
    soundEngine = new SoundEngine();
    particleManager = new ParticleManager();
    uiRenderer = new UiRenderer();
    entityManager = new EntityManager();

    Global::tileManager = &tileManager;
    Global::cursor = &uiRenderer->getCursor();
    Global::physicsEngine = physicsEngine;
    Global::camera = new Camera();

    level = new Level("resource/level/1");
    Global::currentLevel = level;
}

// TODO move sound to separate thread. In case of high load, it starts to sound very wrong
void Rhythm::mainLoop() {

    lastTime = (float)glfwGetTime();

    while (shouldContinue) {

        shouldContinue = !glfwWindowShouldClose(window);

        //PROFILE_SCOPE("mainLoop");
        glfwPollEvents();

        auto now = (float)glfwGetTime();
        float diff = now - lastTime;

        inputHandler->processKeyboardInput(diff);
        inputHandler->processMouseClickInput();
        inputHandler->processMouseInput();

        BeatManager::onUpdate();
        physicsEngine->onUpdate(diff);
        soundEngine->onUpdate(diff);
        particleManager->onUpdate(diff);
        entityManager->onUpdate(diff);
        level->onUpdate(diff);
        Global::camera->onUpdate(diff);

        level->onRender();
        entityManager->onRender();
        particleManager->onRender();
        uiRenderer->onRender();

        lastTime = now;

        renderImGui();
        glfwSwapBuffers(window);
    }
}

void Rhythm::cleanup() {
    delete level; //WARN this has to be cleared before entity manager since both delete from entity manager, so we don't get double free
    delete inputHandler;
    delete uiRenderer;
    delete physicsEngine;
    delete soundEngine;
    delete entityManager;

    delete Global::camera;

    RhythmMultiplier::cleanUp();
    BeatOffsetType::cleanUp();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}
