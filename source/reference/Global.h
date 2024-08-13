//
// Created by Alienson on 1.8.2024..
//

#ifndef RHYTHM_GLOBAL_H
#define RHYTHM_GLOBAL_H

#include "Reference.h"
#include "entity/Player.h"

class Global{
public:
    static void init(){
        player = new Player(Textures::BIKER);
        player->scale = glm::vec2(0.1,0.1);
        player->stateMachine = *SpriteStateMachine(9, 8)
                .addTransitionsForState(0, {})
                ->addTransitionsForState(1, {})
                ->addTransitionsForState(2, {})
                ->addTransitionsForState(3, {})
                ->addTransitionsForState(4, {})
                ->addTransitionsForState(5, {})
                ->addTransitionsForState(6, {})
                ->addTransitionsForState(7, {})
                ->addTransitionsForState(8, {});
        player->stateMachine.setTexturesCount({6, 8, 6, 4, 6, 2, 4, 6, 6});
    }
    static inline Player* player = nullptr; //TODO make it not pointer
    static inline Sprite* cursor = nullptr;
};

#endif //RHYTHM_GLOBAL_H
