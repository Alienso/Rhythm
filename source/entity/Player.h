//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_PLAYER_H
#define RHYTHM_PLAYER_H


#include "Entity.h"
#include "reference/Reference.h"

class Player : public Entity{

public:
    Player();
    ~Player() override = default;

    void onUpdate(float deltaTime);
    [[nodiscard]] bool canAttack() const;
    void attack();

    Entity mist{Textures::MIST};
    Sprite weapon{Textures::PISTOL};

    float attackCD = 0.2;

private:

};


#endif //RHYTHM_PLAYER_H
