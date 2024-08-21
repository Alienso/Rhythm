//
// Created by Alienson on 21.4.2024..
//

#include "InputHandler.h"
#include "reference/Configuration.h"
#include "reference/Global.h"
#include "entity/SpriteStates.h"
#include "Rhythm.h"

#include <GLFW/glfw3.h>

void InputHandler::processMouseInput() {

    if (glfwGetInputMode(app->window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
        return;
    }

    double xposIn, yposIn;
    glfwGetCursorPos(app->window, &xposIn, &yposIn);

    int xpos = (int)xposIn;
    int ypos = (int)yposIn;

    if (xpos > Configuration::windowWidth) {
        xpos = Configuration::windowWidth;
        glfwSetCursorPos(app->window, xpos, ypos);
    }
    else if (xpos < -Configuration::windowWidth) {
        xpos = -Configuration::windowWidth;
        glfwSetCursorPos(app->window, xpos, ypos);
    }
    if (ypos > Configuration::windowHeight) {
        ypos = Configuration::windowHeight;
        glfwSetCursorPos(app->window, xpos, ypos);
    }
    else if (ypos < -Configuration::windowHeight) {
        ypos = -Configuration::windowHeight;
        glfwSetCursorPos(app->window, xpos, ypos);
    }

    float xoffset = xpos - app->uiRenderer->previousCursorPos.x;
    float yoffset = ypos - app->uiRenderer->previousCursorPos.y;
    app->uiRenderer->previousCursorPos.x = app->uiRenderer->getCursor().translate.x;
    app->uiRenderer->previousCursorPos.y = app->uiRenderer->getCursor().translate.y;

    xoffset *= Configuration::mouseSensitivity;
    yoffset *= Configuration::mouseSensitivity;

    glm::vec2 newPos = { (app->uiRenderer->previousCursorPos.x + xoffset) / (float)Configuration::windowWidth,
                         - (app->uiRenderer->previousCursorPos.y + yoffset) / (float)Configuration::windowHeight };
    app->uiRenderer->getCursor().translate = newPos;

}

void InputHandler::processMouseClickInput() {

    if (glfwGetInputMode(app->window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
        return;
    }

    if (glfwGetMouseButton(app->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        if (Global::player->canAttack()) {
            Global::player->attack();
            World::score=Global::soundEngine->doAction();
        }
    }
}

void InputHandler::processKeyboardInput(double deltaTime) {
    if (glfwGetKey(app->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        int mode = glfwGetInputMode(app->window, GLFW_CURSOR);
        glfwSetInputMode(app->window, GLFW_CURSOR, mode == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    } else if (glfwGetKey(app->window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(app->window, true);
    }

    Entity& player = *Global::player;
    player.previousPos = player.pos;

    if (glfwGetKey(app->window, GLFW_KEY_A) == GLFW_PRESS) {
        player.movementVec.x = -1.0;
        player.sprite.invertTex = true;
        if (player.sprite.stateMachine.getState() != PLAYER_JUMP)
            player.sprite.stateMachine.changeState(PLAYER_RUN);
    }
    if (glfwGetKey(app->window, GLFW_KEY_D) == GLFW_PRESS) {
        player.movementVec.x = 1.0;
        player.sprite.invertTex = false;
        if (player.sprite.stateMachine.getState() != PLAYER_JUMP)
            player.sprite.stateMachine.changeState(PLAYER_RUN);
    }
    else if(glfwGetKey(app->window, GLFW_KEY_A) == GLFW_RELEASE) {
        player.movementVec.x = 0;
        if (player.sprite.stateMachine.getState() != PLAYER_JUMP)
        player.sprite.stateMachine.changeState(PLAYER_IDLE);
    }
    if (glfwGetKey(app->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (player.onGround) {
            player.movementVec.y = 3.5;
            player.onGround = false;
            player.sprite.stateMachine.changeState(PLAYER_JUMP);
        }
    }else if (glfwGetKey(app->window, GLFW_KEY_SPACE) == GLFW_RELEASE){
        if (player.movementVec.y > 0)
            player.movementVec.y /= 3;
    }
    if (player.onGround){
        if (player.movementVec.x == 0 && player.movementVec.y == 0)
            player.sprite.stateMachine.changeState(PLAYER_IDLE);
        else
            player.sprite.stateMachine.changeState(PLAYER_RUN);
    }
}
