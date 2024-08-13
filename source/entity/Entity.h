//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_ENTITY_H
#define RHYTHM_ENTITY_H


#include "Sprite.h"

class Entity : public Sprite{

public:
    explicit Entity(Texture* texture);

    glm::vec2 previousPos = {0,0};
    glm::vec2 movementVec = {0,0};

    float speedModifier = 1.0f;
    bool onGround = true;

};


#endif //RHYTHM_ENTITY_H
