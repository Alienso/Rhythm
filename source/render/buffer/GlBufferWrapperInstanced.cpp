//
// Created by Alienson on 6.9.2024..
//

#include "GlBufferWrapperInstanced.h"
#include "entity/Sprite.h"

GlBufferWrapperInstanced::GlBufferWrapperInstanced(){

}

void GlBufferWrapperInstanced::initialize(std::vector<glm::fvec2>& offsets, float scale){

    float quadVertices[24];
    memcpy(quadVertices, quadVerticesScaled, sizeof(quadVertices));
    for (int i=0; i<6; i++)
        for (int j=0; j<2; j++)
            quadVertices[i * 4 + j] *= scale;

    quadVb.initialize(quadVertices , sizeof(quadVertices));
    instanceVb.initialize((float*)&(offsets[0]), offsets.size() * sizeof(glm::fvec2));

    quadLayout = VertexBufferLayout();
    quadLayout.push<float>(2);
    quadLayout.push<float>(2);

    instanceLayout = VertexBufferLayout();
    instanceLayout.push<float>(2,1);

    va.addBuffer(quadVb, quadLayout);
    va.addInstanceBuffer(instanceVb, instanceLayout, 2);
}