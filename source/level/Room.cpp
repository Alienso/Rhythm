//
// Created by Alienson on 20.4.2025..
//

#include "Room.h"
#include <GLFW/glfw3.h>

Room::Room() {
    /*weaves.emplace_back(Weave{});
    weaves.emplace_back(Weave{});
    currentWeaveIndex = 0;*/
    currentWeaveStartTime = lastWeaveClearTime = (float)glfwGetTime();
}

void Room::onUpdate(float deltaTime) {
    Weave& currentWeave = getCurrentWeave();
    float timeNow = (float)glfwGetTime();
    switch (status) {
        case PRE_WEAVE:
            if (timeNow - lastWeaveClearTime > currentWeave.startDelay){
                status = WEAVE_IN_PROGRESS;
                currentWeaveStartTime = timeNow;
            }
            break;
        case WEAVE_IN_PROGRESS:
            if (currentWeave.enemiesLeft <= currentWeave.minEnemiesAliveForNext){
                lastWeaveClearTime = (float)glfwGetTime();
                status = POST_WEAVE;
            }
            if (currentWeave.getNextSpawn() != nullptr && timeNow - currentWeaveStartTime > currentWeave.getNextSpawn()->spawnDelay)
                currentWeave.spawnNext();

            break;
        case POST_WEAVE:
            while (currentWeave.getNextSpawn() != nullptr)
                currentWeave.spawnNext();
            status = PRE_WEAVE;

            if (currentWeaveIndex + 1 < weaves.size())
                currentWeaveIndex++;
            else status = ROOM_FINISHED;

            break;
        case ROOM_FINISHED:
            break;
    }
}

Weave &Room::getCurrentWeave() {
    return weaves[currentWeaveIndex];
}
