//
// Created by Alienson on 1.8.2024..
//

#ifndef RHYTHM_GLOBAL_H
#define RHYTHM_GLOBAL_H

#include "Reference.h"
#include "entity/Player.h"
#include "sound/SoundEngine.h"
#include "manager/ParticleManager.h"
#include "PhysicsEngine.h"
#include "manager/EntityManager.h"

class Global{
public:
    static void init(){}

    static inline Player* player = nullptr; // TODO maybe use player directly from Entity Manager
    static inline Sprite* cursor = nullptr;

    static inline EntityManager* entityManger = nullptr;
    static inline PhysicsEngine* physicsEngine = nullptr;
    static inline SoundEngine* soundEngine = nullptr;
    static inline ParticleManager* particleManager = nullptr;
};

#endif //RHYTHM_GLOBAL_H
