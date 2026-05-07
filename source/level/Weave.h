//
// Created by Alienso on 20.4.2025.
//

#ifndef RHYTHM_WEAVE_H
#define RHYTHM_WEAVE_H

#include <vector>
#include <glm/vec2.hpp>
#include "entity/EntityLiving.h"

struct Spawn{
    Spawn(glm::vec2 pos, EntityLiving* entity, float spawnDelay);
    glm::vec2 pos;
    EntityLiving* entity;
    float spawnDelay = 0;
};

class Weave {
public:
    Weave(float startDelay, int minEnemiesAlive, std::vector<Spawn>& spawns);

    void spawnNext();
    Spawn* getNextSpawn();

    float startDelay = 0;
    int minEnemiesAliveForNext = 0;
    int enemiesLeft = 0;
    std::vector<Spawn> spawns;

private:
    unsigned int currentSpawnIndex = 0;
};


#endif //RHYTHM_WEAVE_H
