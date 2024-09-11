//
// Created by Alienson on 1.8.2024..
//

#include "Rhythm.h"

#include "glad.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "stb_image.h"
#include "reference/Configuration.h"
#include "InputHandler.h"
#include "reference/Global.h"

#include <iostream>
#include <unistd.h>

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
    glfwSwapInterval(1);

    GLFWimage images[1];
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
    ImGui::Text("Score: %.2f", Level::score / 48000.0);
    ImGui::Text("Player Pos: %.2f %.2f", entityManager->player.pos.x, entityManager->player.pos.y);
    //ImGui::Text("Player BB: minX: %.2f, maxX: %.2f, minY: %.2f, maxY: %.2f", entityManager->player.collisionBB.minX, entityManager->player.collisionBB.maxX, entityManager->player.collisionBB.minY, entityManager->player.collisionBB.maxY);

    if (ImGui::Button("Seek+"))
        soundEngine->seek(10);
    if (ImGui::Button("Seek-"))
        soundEngine->seek(-10);

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

    Global::init();

    inputHandler = new InputHandler(this);
    physicsEngine = new PhysicsEngine();
    soundEngine = new SoundEngine();
    particleManager = new ParticleManager();
    uiRenderer = new UiRenderer();
    entityManager = new EntityManager();

    Global::textureManager = &textureManager;
    Global::cursor = &uiRenderer->getCursor();

    level = new Level("resource/level/1.lvl");
}

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

        physicsEngine->onUpdate(diff);
        soundEngine->onUpdate(diff);
        particleManager->onUpdate(diff);
        entityManager->onUpdate(diff);
        level->onUpdate(diff);

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
    delete inputHandler;
    delete uiRenderer;
    delete physicsEngine;
    delete soundEngine;
    delete entityManager;
    delete level;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}
