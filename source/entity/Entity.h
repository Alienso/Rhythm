//
// Created by Alienso on 10.8.2024.
//

#ifndef RHYTHM_ENTITY_H
#define RHYTHM_ENTITY_H


#include "render/sprite/Sprite.h"
#include "physics/AxisAlignedBB.h"

class Entity{

public:
    explicit Entity(Texture* texture);
    virtual ~Entity();

    virtual void onRender() const;
    virtual void onUpdate(float deltaTime);

    [[nodiscard]] const glm::vec2& pos() const;

    void moveBy(float x, float y);
    void moveTo(float x, float y);

    glm::vec2 previousPos = {0,0};
    glm::vec2 movementVec = {0,0};

    float speedModifier = 1.0f; //TODO move //TODO where?
    bool onGround = false;
    Sprite sprite;
    AxisAlignedBB collisionBB;

protected:
    glm::vec2 pos_ = {0,0};
    Sprite collisionSprite;

    virtual void rebuildCollisionBoxes();
};


#endif //RHYTHM_ENTITY_H
