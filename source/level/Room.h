//
// Created by Alienson on 20.4.2025..
//

#ifndef RHYTHM_ROOM_H
#define RHYTHM_ROOM_H

#include <vector>
#include <glm/vec2.hpp>
#include "Weave.h"

enum RoomStatus{
    PRE_WEAVE, WEAVE_IN_PROGRESS, POST_WEAVE, ROOM_FINISHED
};

class Room {
public:
    Room();

    void onUpdate(float deltaTime);

    Weave& getCurrentWeave();

    glm::vec2 cameraBoundaries = {0,0}; //TODO
    std::vector<Weave> weaves;

private:
    unsigned int currentWeaveIndex = 0;
    float lastWeaveClearTime = 0.0f; //There can be a pause between clearing the weave and beginning of the next one
    float currentWeaveStartTime = 0.0f;
    RoomStatus status = PRE_WEAVE;

};


#endif //RHYTHM_ROOM_H
