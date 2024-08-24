//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_PLAYER_H
#define RHYTHM_PLAYER_H


#include "EntityLiving.h"
#include "reference/Reference.h"

class Player : public EntityLiving{

public:
    Player();
    ~Player() override = default;

    void onUpdate(float deltaTime) override;
    [[nodiscard]] bool canAttack() const;
    void attack();

    Entity mist{Textures::MIST};
    Sprite weapon{Textures::PISTOL};

    float attackCD = 0.2;

private:

};


#endif //RHYTHM_PLAYER_H
