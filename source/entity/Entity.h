//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_ENTITY_H
#define RHYTHM_ENTITY_H


#include "Sprite.h"

class Entity{

public:
    explicit Entity(Texture* texture);
    virtual ~Entity();

    virtual void onRender() const;
    virtual void onUpdate();

    glm::vec2 pos = {0,0};
    glm::vec2 previousPos = {0,0};
    glm::vec2 movementVec = {0,0};

    float speedModifier = 1.0f;
    bool onGround = true;

    Sprite sprite;

};


#endif //RHYTHM_ENTITY_H
