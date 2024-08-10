//
// Created by Alienson on 10.8.2024..
//

#include "Player.h"
#include "Global.h"

Player::Player(Texture *texture) : Entity(texture) {
    weapon.scale = {0.025, 0.025};
}

void Player::onUpdate() {
    weapon.pos = {pos.x, pos.y + 0.1};
    weapon.rotation = atan2((Global::cursor->pos.y - weapon.pos.y), (Global::cursor->pos.x - weapon.pos.x)) - 3.1415/4.0; //TODO fix this texture to not do this offset
}