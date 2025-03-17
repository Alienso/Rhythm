//
// Created by Alienson on 10.8.2024..
//

#ifndef RHYTHM_UIRENDERER_H
#define RHYTHM_UIRENDERER_H


#include "entity/Sprite.h"
#include "reference/Reference.h"

class UiRenderer {

public:
    UiRenderer();
    void onRender();

    Sprite& getCursor();

    glm::vec2 previousCursorPos = {0,0}; //TODO
    static bool showCollisionBoxes;
private:
    Sprite cursor{Textures::CURSOR};
    Sprite multiplierFrame{Textures::MULTIPLIER_FRAME};
    Sprite multiplierFlame{Textures::FLAME_CIRCLE, 12};
    Sprite collisionBox{Textures::COLLISION_BOX};

    void renderCollisionBoxes();
};


#endif //RHYTHM_UIRENDERER_H
