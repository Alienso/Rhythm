//
// Created by Alienson on 20.4.2025..
//

#include <algorithm>

#include "Weave.h"
#include "reference/Global.h"

static int sortBySpawnDelay(const Spawn& x, const Spawn& y){
    return x.spawnDelay < y.spawnDelay;
}

Spawn::Spawn(glm::vec2 pos, EntityLiving *entity, float spawnDelay) : pos(pos), entity(entity), spawnDelay(spawnDelay) {

}

Weave::Weave(float startDelay, int minEnemiesAlive, std::vector<Spawn> &spawns) : startDelay(startDelay), minEnemiesAliveForNext(minEnemiesAlive), spawns(spawns) {
    enemiesLeft = (int)spawns.size();
    /* TODO
     * With minEnemiesAliveForNext > 0, the weave can end while some enemies haven't spawned yet.
     * POST_WEAVE then force-spawns them. Those untracked enemies die → decrement next weave's counter (Bug 1 amplified).
     * Not a problem with your current .room file (minEnemiesAliveForNext = 0) but breaks with any other value.
     */
    std::sort(spawns.begin(), spawns.end(), sortBySpawnDelay);
}

void Weave::spawnNext() {
    assert(currentSpawnIndex < spawns.size());
    Global::entityManger->spawnEntity(spawns[currentSpawnIndex++].entity);
    //TODO enemiesAlive tracking?
}

Spawn* Weave::getNextSpawn() {
    if (currentSpawnIndex >= spawns.size())
        return nullptr;
    return &spawns[currentSpawnIndex];
}