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