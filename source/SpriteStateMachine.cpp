//
// Created by Alienson on 8.8.2024..
//

#include <cstdlib>
#include "SpriteStateMachine.h"
#include "GLFW/glfw3.h"

SpriteStateMachine::SpriteStateMachine() {
    startTime = (float)glfwGetTime();
}

SpriteStateMachine::SpriteStateMachine(unsigned int states, unsigned int textureWidth) : textureWidth(textureWidth) {
    startTime = (float)glfwGetTime();
    transitions.resize(states);
}

SpriteStateMachine * SpriteStateMachine::addTransitionsForState(unsigned int state, std::vector<unsigned int> transitions) {
    if (state >= this->transitions.size()){
        this->transitions.resize(state + 1);
    }
    this->transitions[state] = transitions;
    return this;
}

std::vector<unsigned int> &SpriteStateMachine::getTransitionsForState() {
    return transitions[state];
}

void SpriteStateMachine::changeState(unsigned int state) {
    //TODO
    if (state == this->state)
        return;
    if (state >= transitions.size()){
        exit(1);
    }
    startTime = (float)glfwGetTime();
    this->state = state;
}

unsigned int SpriteStateMachine::getState() const {
    return state;
}

unsigned int SpriteStateMachine::getStateCount() const {
    return transitions.size();
}

unsigned int SpriteStateMachine::getAnimationState() const {
    return (unsigned int)(((float)glfwGetTime() - startTime) / (animationSpeed / (float)textureCountForState[state])) % textureCountForState[state];
}

void SpriteStateMachine::setTexturesCount(std::vector<unsigned int> textureCount) {
    this->textureCountForState = std::move(textureCount);
}

unsigned int SpriteStateMachine::getTextureCountForState() const {
    return textureCountForState[state];
}

unsigned int SpriteStateMachine::getTextureWidth() const {
    return textureWidth;
}
