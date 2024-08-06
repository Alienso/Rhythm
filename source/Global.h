//
// Created by Alienson on 1.8.2024..
//

#ifndef RHYTHM_GLOBAL_H
#define RHYTHM_GLOBAL_H

#include "render/Sprite.h"
#include "Assets.h"

class Global{
public:
    static void init(){
        player = new Sprite();
        player->addState(0, Textures::BLANK);
    }
    static inline Sprite* player = nullptr; //TODO make it not pointer
};

#endif //RHYTHM_GLOBAL_H
