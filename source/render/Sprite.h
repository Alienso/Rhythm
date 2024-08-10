//
// Created by Alienson on 3.8.2024..
//

#ifndef RHYTHM_SPRITE_H
#define RHYTHM_SPRITE_H

#include "Texture.h"
#include "glm/vec2.hpp"
#include "glm/mat3x3.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "render/buffer/GlBufferWrapper.h"

#include "Configuration.h"
#include "SpriteStateMachine.h"

inline float quadVertices[] = {
        // positions // texture Coords
        -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,

        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
};

inline float quadVerticesScaled[] = {
        // positions // texture Coords
        -1.0f/Configuration::aspectRatio,  1.0f, 0.0f, 1.0f,
        -1.0f/Configuration::aspectRatio, -1.0f, 0.0f, 0.0f,
        1.0f/Configuration::aspectRatio,  1.0f, 1.0f, 1.0f,

        1.0f/Configuration::aspectRatio,  1.0f, 1.0f, 1.0f,
        -1.0f/Configuration::aspectRatio, -1.0f, 0.0f, 0.0f,
        1.0f/Configuration::aspectRatio, -1.0f, 1.0f, 0.0f,
};

class Sprite {

public:
    explicit Sprite(Texture* texture);
    [[nodiscard]] Texture* getTexture() const;

    void bind() const;

    glm::vec2 pos = {0,0};
    glm::vec2 scale = {1.0,1.0};
    float rotation = 0;

    glm::vec2 previousPos = {0,0};
    glm::vec2 movementVec = {0,0};

    float speedModifier = 1.0f;
    bool onGround = true;

    SpriteStateMachine stateMachine;

private:
    Texture* texture = nullptr;
    GlBufferWrapper glBufferWrapper{quadVerticesScaled, sizeof(quadVerticesScaled) / sizeof(float)};
    glm::mat3x3 transformationMatrix = glm::identity<glm::mat3x3>();

};


#endif //RHYTHM_SPRITE_H
