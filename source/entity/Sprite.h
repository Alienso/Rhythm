//
// Created by Alienson on 3.8.2024..
//

#ifndef RHYTHM_SPRITE_H
#define RHYTHM_SPRITE_H

#include "render/Texture.h"
#include "glm/vec2.hpp"
#include "glm/mat3x3.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "render/buffer/GlBufferWrapper.h"

#include "reference/Configuration.h"
#include "entity/SpriteStateMachine.h"

inline float quadVertices[] = {
        // positions // texture Coords
        -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,

        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
};

/*inline float quadVerticesScaled[] = {
        // positions // texture Coords
        -1.0f/Configuration::aspectRatio,  1.0f, 0.0f, 1.0f,
        -1.0f/Configuration::aspectRatio, -1.0f, 0.0f, 0.0f,
        1.0f/Configuration::aspectRatio,  1.0f, 1.0f, 1.0f,

        1.0f/Configuration::aspectRatio,  1.0f, 1.0f, 1.0f,
        -1.0f/Configuration::aspectRatio, -1.0f, 0.0f, 0.0f,
        1.0f/Configuration::aspectRatio, -1.0f, 1.0f, 0.0f,
};*/

struct AffineTransformations{
    AffineTransformations(glm::vec2 translation, glm::vec2 scale, float rotation) : translation(translation), scale(scale), rotation(rotation){}
    glm::vec2 translation = {0,0};
    glm::vec2 scale = {1.0,1.0};
    float rotation = 0;
};

class Entity;

class Sprite {

public:
    explicit Sprite(Texture* texture);
    Sprite(Texture* texture, unsigned int animationStates);
    [[nodiscard]] Texture* getTexture() const;

    void bind() const;
    void onRender() const;

    glm::vec2 translate = {0,0};
    glm::vec2 scale = {1.0,1.0};
    float rotation = 0;
    bool invertTex = false;

    SpriteStateMachine stateMachine;
    friend Entity;

protected:
    Texture* texture = nullptr;
    Entity* parent = nullptr; //TODO
    GlBufferWrapper glBufferWrapper{quadVertices, sizeof(quadVertices) / sizeof(float)};
};


#endif //RHYTHM_SPRITE_H
