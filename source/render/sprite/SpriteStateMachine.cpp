//
// Created by Alienson on 8.8.2024..
//

#include "SpriteStateMachine.h"
#include "GLFW/glfw3.h"

#include <utility>

SpriteStateMachine::SpriteStateMachine() {
    startTime = (float)glfwGetTime();
    textureCountForState.push_back(1);
}

SpriteStateMachine::SpriteStateMachine(unsigned int stateCount, unsigned int textureWidth) : stateCount(stateCount), textureWidth(textureWidth) {
    startTime = (float)glfwGetTime();
}

void SpriteStateMachine::changeState(unsigned int state) {
    if (state == this->state)
        return;
    startTime = (float)glfwGetTime();
    this->state = state;
}

unsigned int SpriteStateMachine::getState() const {
    return state;
}

unsigned int SpriteStateMachine::getStateCount() const {
    return stateCount;
}

unsigned int SpriteStateMachine::getAnimationState() const {
    return (unsigned int)(((float)glfwGetTime() - startTime) / (animationSpeed / (float)textureCountForState[state])) % textureCountForState[state];
}

void SpriteStateMachine::setTexturesCount(std::vector<unsigned int> textureCount) {
    this->textureCountForState = std::move(textureCount);
}

unsigned int SpriteStateMachine::getTextureWidth() const {
    return textureWidth;
}
