//
// Created by Alienson on 8.8.2024..
//

#ifndef RHYTHM_SPRITESTATEMACHINE_H
#define RHYTHM_SPRITESTATEMACHINE_H


#include <vector>

class SpriteStateMachine {

public:
    SpriteStateMachine();
    explicit SpriteStateMachine(unsigned int states, unsigned int textureWidth);

    SpriteStateMachine* addTransitionsForState(unsigned int state, std::vector<unsigned int> transitions);
    [[nodiscard]] std::vector<unsigned int>& getTransitionsForState();
    void changeState(unsigned int state);
    [[nodiscard]] unsigned int getState() const;
    [[nodiscard]] unsigned int getStateCount() const;
    [[nodiscard]] unsigned int getAnimationState() const;

    void setTexturesCount(std::vector<unsigned int> textureCount);
    [[nodiscard]] unsigned int getTextureCountForState() const;
    [[nodiscard]] unsigned int getTextureWidth() const;

    //TODO for debugging purposes only move down
    float animationSpeed = 0.7f;
    unsigned int state = 0;

private:
    //unsigned int state = 0;
    std::vector<std::vector<unsigned int>> transitions;
    std::vector<unsigned int> textureCountForState;
    unsigned int textureWidth = 1;
    float startTime;
    //float animationSpeed = 0.15f;
};


#endif //RHYTHM_SPRITESTATEMACHINE_H
