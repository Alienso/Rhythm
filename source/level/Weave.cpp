//
// Created by Alienson on 20.4.2025..
//

#include "Weave.h"
#include "entity/enemy/Nightmare.h"
#include "reference/Global.h"

Spawn::Spawn(glm::vec2 pos, EntityLiving *entity, float spawnDelay) : pos(pos), entity(entity), spawnDelay(spawnDelay) {

}

Weave::Weave() {
    /*startDelay = 2.0f;
    minEnemiesAliveForNext = 0;
    spawns.emplace_back(glm::vec2{1.0, 0.0}, new Nightmare(), 0.5f);
    spawns.emplace_back(glm::vec2{0.0, 0.0}, new Nightmare(), 1.5f);*/

    enemiesLeft = (int)spawns.size();
}

Weave::Weave(float startDelay, int minEnemiesAlive, std::vector<Spawn> &spawns) : startDelay(startDelay),
    minEnemiesAliveForNext(minEnemiesAlive), spawns(spawns) {

    enemiesLeft = (int)spawns.size();
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