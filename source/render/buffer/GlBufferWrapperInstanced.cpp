//
// Created by Alienson on 6.9.2024..
//

#include "GlBufferWrapperInstanced.h"
#include "entity/Sprite.h"

#include <cstring>

GlBufferWrapperInstanced::GlBufferWrapperInstanced(){

}

void GlBufferWrapperInstanced::initialize(std::vector<glm::fvec2>& offsets, glm::vec2 scale){

    float vertices[24];
    memcpy(vertices, quadVertices, sizeof(vertices));
    for (int i=0; i<6; i++) {
        vertices[i * 4] *= scale.x;
        vertices[i * 4 + 1] *= scale.y;
    }


    quadVb.initialize(vertices , sizeof(vertices));
    instanceVb.initialize((float*)&(offsets[0]), offsets.size() * sizeof(glm::fvec2));

    quadLayout = VertexBufferLayout();
    quadLayout.push<float>(2);
    quadLayout.push<float>(2);

    instanceLayout = VertexBufferLayout();
    instanceLayout.push<float>(2,1);

    va.addBuffer(quadVb, quadLayout);
    va.addInstanceBuffer(instanceVb, instanceLayout, 2);
}