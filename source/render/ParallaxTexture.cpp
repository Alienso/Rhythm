//
// Created by Alienson on 1.9.2024..
//

#include "ParallaxTexture.h"
#include "glad/glad.h"
#include "Shader.h"
#include "reference/Reference.h"
#include <cassert>

ParallaxTexture::ParallaxTexture(std::vector<const char *> paths, std::vector<float> speedModifiers) {

    assert(paths.size() == speedModifiers.size());

    this->glBuffers.reserve(speedModifiers.size());

    for (size_t i=0; i<speedModifiers.size(); i++) {

        textures.push_back(new Texture(paths[i], GL_RGBA));

        const float aspectRatio = (float)textures[i]->width / (float)textures[i]->height;
        float vertices[24] = {
                // positions // texture Coords
                -1.0f,  1.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 1.0f / aspectRatio * Configuration::aspectRatio, 1.0f,

                1.0f,  1.0f, 1.0f / aspectRatio * Configuration::aspectRatio, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f,
                1.0f, -1.0f, 1.0f / aspectRatio * Configuration::aspectRatio, 0.0f,
        };

        this->aspectRatios.push_back(aspectRatio);
        this->speedModifiers.push_back(speedModifiers[i]);
        this->offsets.push_back(0);
        this->glBuffers.emplace_back(vertices, sizeof (vertices) / sizeof(float));
    }
}

ParallaxTexture::~ParallaxTexture() {
    for (Texture* tex : textures)
        delete tex;
}

void ParallaxTexture::translate(float x) {
    for (size_t i=0; i<offsets.size(); i++){
        offsets[i] += x * speedModifiers[i];
        /*if (offsets[i] > 1 - aspectRatios[i])
            offsets[i] = 1 - aspectRatios[i];
        if (offsets[i] < -1)
            offsets[i] = -1;*/
    }
}

void ParallaxTexture::onRender() const {
    Shader* shader = Shaders::TEXTURE_PARALLAX;
    shader->use();

    for (size_t i=0; i<textures.size(); i++) {
        textures[i]->bind(0);
        glBuffers[i].va.bind();

        shader->setInt("texture1", 0);
        shader->setFloat("offset", offsets[i]);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
