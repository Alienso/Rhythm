//
// Created by Alienson on 8.8.2024..
//

#ifndef RHYTHM_SPRITESTATEMACHINE_H
#define RHYTHM_SPRITESTATEMACHINE_H

#include <vector>

//TODO make a new class SpriteSheet so fields related to that are moved there. Only the animation logic should remain here.
class SpriteStateMachine {

public:
    SpriteStateMachine();
    SpriteStateMachine(unsigned int stateCount, unsigned int textureWidth);

    void changeState(unsigned int state);
    [[nodiscard]] unsigned int getState() const; //Texture table row
    [[nodiscard]] unsigned int getStateCount() const;
    [[nodiscard]] unsigned int getAnimationFrame() const; //Texture Table column
    [[nodiscard]] unsigned int getTextureWidth() const;

    void setTexturesCount(std::vector<unsigned int> textureCount);

    //TODO this is public for debugging purposes only. Move to private afterwards
    float animationSpeed = 0.7f;

private:
    unsigned int state = 0;
    unsigned int stateCount = 1;
    //TODO some of this fields don't need to be in each instance of the class
    std::vector<unsigned int> textureCountForStates; //Number of frames for each state sorted by texture rows
    unsigned int textureWidth = 1;
    float startTime;
};


#endif //RHYTHM_SPRITESTATEMACHINE_H
