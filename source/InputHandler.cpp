//
// Created by Alienson on 21.4.2024..
//

#include "InputHandler.h"
#include "Configuration.h"

#include <GLFW/glfw3.h>

void InputHandler::processMouseInput() {

    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
        return;
    }

    double xposIn, yposIn;
    glfwGetCursorPos(window, &xposIn, &yposIn);

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    /*if (Global::player->getCamera().firstMouse) {
        Global::player->getCamera().lastMousePos[0] = xpos;
        Global::player->getCamera().lastMousePos[1] = ypos;
        Global::player->getCamera().firstMouse = false;
    }

    float xoffset = xpos - Global::player->getCamera().lastMousePos[0];
    float yoffset = Global::player->getCamera().lastMousePos[1] - ypos;
    Global::player->getCamera().lastMousePos[0] = xpos;
    Global::player->getCamera().lastMousePos[1] = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    Global::player->getCamera().yaw += xoffset;
    Global::player->getCamera().pitch += yoffset;

    if (Global::player->getCamera().pitch > 89.0f)
        Global::player->getCamera().pitch = 89.0f;
    if (Global::player->getCamera().pitch < -89.0f)
        Global::player->getCamera().pitch = -89.0f;*/

}

void InputHandler::processKeyboardInput(double deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        int mode = glfwGetInputMode(window, GLFW_CURSOR);
        glfwSetInputMode(window, GLFW_CURSOR,
                         mode == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    } else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    double cameraSpeed = 20.0 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraSpeed /= 3;

    /*Global::player->prevPos = Global::player->pos;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Global::player->pos += cameraSpeed * Global::player->getCamera().front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Global::player->pos -= cameraSpeed * Global::player->getCamera().front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Global::player->pos -= glm::normalize(glm::cross(Global::player->getCamera().front, Global::player->getCamera().up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Global::player->pos += glm::normalize(glm::cross(Global::player->getCamera().front, Global::player->getCamera().up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Global::player->pos += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        Global::player->pos += cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f);*/
}
