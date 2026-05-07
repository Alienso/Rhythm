//
// Created by Alienso on 10.8.2024.
//

#ifndef RHYTHM_UIRENDERER_H
#define RHYTHM_UIRENDERER_H


#include "render/sprite/Sprite.h"
#include "reference/Reference.h"

class UiRenderer {

public:
    UiRenderer();
    void onRender();

    Sprite& getCursor();

    static bool showCollisionBoxes;
private:
    Sprite cursor{Textures::CURSOR};
    Sprite multiplierFrame{Textures::MULTIPLIER_FRAME};
    Sprite multiplierFlame{Textures::FLAME_CIRCLE, 12};
    Sprite collisionBox{Textures::COLLISION_BOX};

    void renderCollisionBoxes();
};


#endif //RHYTHM_UIRENDERER_H
