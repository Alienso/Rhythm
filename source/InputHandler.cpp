//
// Created by Alienson on 21.4.2024..
//

#include "InputHandler.h"
#include "Configuration.h"
#include "Global.h"
#include "SpriteStates.h"

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
        glfwSetInputMode(window, GLFW_CURSOR, mode == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    } else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    Sprite& player = *Global::player;
    player.previousPos = player.pos;
    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //    player.pos += cameraSpeed * player.getCamera().front;
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //    player.pos -= cameraSpeed * player.getCamera().front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player.movementVec.x = -1.0;
        player.invertTex = true;
        if (player.stateMachine.getState() != PLAYER_JUMP)
            player.stateMachine.changeState(PLAYER_RUN);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player.movementVec.x = 1.0;
        player.invertTex = false;
        if (player.stateMachine.getState() != PLAYER_JUMP)
            player.stateMachine.changeState(PLAYER_RUN);
    }
    else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
        player.movementVec.x = 0;
        if (player.stateMachine.getState() != PLAYER_JUMP)
        player.stateMachine.changeState(PLAYER_IDLE);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (player.onGround) {
            player.movementVec.y = 3.5;
            player.onGround = false;
            player.stateMachine.changeState(PLAYER_JUMP);
        }
    }
    if (player.onGround){
        if (player.movementVec.x == 0 && player.movementVec.y == 0)
            player.stateMachine.changeState(PLAYER_IDLE);
        else
            player.stateMachine.changeState(PLAYER_RUN);
    }
    //if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    //    player.pos += cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
}
