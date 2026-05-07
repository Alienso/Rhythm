//
// Created by Alienso on 8.8.2024.
//

#include "SpriteStateMachine.h"
#include "GLFW/glfw3.h"

#include <utility>

SpriteStateMachine::SpriteStateMachine() {
    startTime = (float)glfwGetTime();
    textureCountForStates.push_back(1);
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

unsigned int SpriteStateMachine::getAnimationFrame() const {
    return (unsigned int)(((float)glfwGetTime() - startTime) / (animationSpeed / (float)textureCountForStates[state])) % textureCountForStates[state];
}

void SpriteStateMachine::setTexturesCount(std::vector<unsigned int> textureCount) {
    this->textureCountForStates = std::move(textureCount);
}

unsigned int SpriteStateMachine::getTextureWidth() const {
    return textureWidth;
}
