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
#include "Configuration.h"
#include "InputHandler.h"
#include "Global.h"

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
    world->onImGuiRender();
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

    world = new World();
    inputHandler = new InputHandler(this);
    physicsEngine = new PhysicsEngine();
    soundEngine = new SoundEngine();
    uiRenderer = new UiRenderer();

    Global::cursor = &uiRenderer->getCursor();
}

void Rhythm::mainLoop() {
    lastTime = glfwGetTime();

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

        world->onUpdate(diff);
        world->onRender();

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
    delete world;
    delete Global::player; //TODO

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}
