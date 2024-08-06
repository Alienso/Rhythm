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

inline float quadVertices[] = {
        // positions // texture Coords
        -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,

        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
};

class Sprite {

public:
    Sprite();

    void addState(unsigned int state, Texture* texture);
    [[nodiscard]] Texture* getTexture(unsigned int state) const;

    void bind() const;

    glm::vec2 translation = {0.0,0.0};
    glm::vec2 scale = {1.0,1.0};
    float rotation = 0;

private:
    std::vector<Texture*> textures = {};
    unsigned int state = 0;
    unsigned int animationStage = 0;

    glm::vec2 pos = {0,0};

    GlBufferWrapper glBufferWrapper{quadVertices, sizeof(quadVertices) / sizeof(float)};
    glm::mat3x3 transformationMatrix = glm::identity<glm::mat3x3>();

};


#endif //RHYTHM_SPRITE_H
