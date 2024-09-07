//
// Created by Alienson on 20.4.2024..
//

#include "GlBufferWrapper.h"
#include "VertexBufferLayout.h"
using namespace std;

GlBufferWrapper::GlBufferWrapper(float *vertices, size_t length) {
    vb.initialize(vertices, length * sizeof(float));
    layout = VertexBufferLayout();
    layout.push<float>(2);
    layout.push<float>(2);
    va.addBuffer(vb, layout);
}