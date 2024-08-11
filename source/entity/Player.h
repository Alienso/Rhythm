//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_PLAYER_H
#define RHYTHM_PLAYER_H


#include "Entity.h"
#include "Assets.h"

class Player : public Entity{

public:
    explicit Player(Texture* texture);

    void onUpdate();

    Entity mist{Textures::MIST};
    Sprite weapon{Textures::PISTOL};
};


#endif //RHYTHM_PLAYER_H
