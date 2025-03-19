//
// Created by Alienson on 8.8.2024..
//

#ifndef RHYTHM_SPRITESTATEMACHINE_H
#define RHYTHM_SPRITESTATEMACHINE_H

#include <vector>
#include <array>

class SpriteStateMachine {

public:
    SpriteStateMachine();
    explicit SpriteStateMachine(unsigned int stateCount, unsigned int textureWidth);

    void changeState(unsigned int state);
    [[nodiscard]] unsigned int getState() const;
    [[nodiscard]] unsigned int getStateCount() const;
    [[nodiscard]] unsigned int getAnimationState() const;
    [[nodiscard]] unsigned int getTextureWidth() const;

    void setTexturesCount(std::vector<unsigned int> textureCount);

    //TODO for debugging purposes only move down
    float animationSpeed = 0.7f;

private:
    unsigned int state = 0;
    unsigned int stateCount = 1;
    //TODO some of this fields don't need to be in each instance of the class
    std::vector<unsigned int> textureCountForState;
    unsigned int textureWidth = 1;
    float startTime;
};


#endif //RHYTHM_SPRITESTATEMACHINE_H
