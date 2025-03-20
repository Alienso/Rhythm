//
// Created by Alienson on 6.9.2024..
//

#include "GlBufferWrapperInstanced.h"
#include "entity/Sprite.h"

#include <cstring>

GlBufferWrapperInstanced::GlBufferWrapperInstanced(){

}

void GlBufferWrapperInstanced::initialize(std::vector<glm::fvec2>& offsets, float scale){

    float vertices[24];
    memcpy(vertices, quadVertices, sizeof(vertices));
    for (int i=0; i<6; i++)
        for (int j=0; j<2; j++)
            vertices[i * 4 + j] *= scale;

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