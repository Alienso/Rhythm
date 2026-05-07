//
// Created by Alienso on 20.4.2025.
//

#include "Room.h"
#include <GLFW/glfw3.h>

Room::Room() {
    currentWeaveIndex = 0;
    currentWeaveStartTime = lastWeaveClearTime = (float)glfwGetTime();
    /*
     * TODO
     * Room is constructed during LevelLoader::loadRooms. If loading takes longer than startDelay (2.0s from your file), the very first PRE_WEAVE check:
     * if (timeNow - lastWeaveClearTime > currentWeave.startDelay)
     * passes immediately on the first frame, skipping the intended delay.
     */
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

            /*
             * This case has an issue
             *
             * currentWeave is bound at function entry to weaves[currentWeaveIndex].
             * Force-spawning is correct. But when those force-spawned enemies die later, EntityManager does:
             *          Global::currentLevel->getCurrentRoom().getCurrentWeave().enemiesLeft--;
             * By that point currentWeaveIndex already points to the next weave.
             * So deaths from force-spawned enemies decrement the wrong weave's enemiesLeft, potentially triggering the next weave to end before it even starts.
             * Fix: Track which weave an entity belongs to at spawn time and use that for decrement, OR don't force-spawn remaining enemies — just clear them.
             *
             */

            while (currentWeave.getNextSpawn() != nullptr)
                currentWeave.spawnNext(); // spawns from OLD weave
            status = PRE_WEAVE;

            if (currentWeaveIndex + 1 < weaves.size())
                currentWeaveIndex++; // THEN advances to next weave
            else status = ROOM_FINISHED;

            break;
        case ROOM_FINISHED:
            break;
    }
}

Weave &Room::getCurrentWeave() {
    return weaves[currentWeaveIndex];
}
