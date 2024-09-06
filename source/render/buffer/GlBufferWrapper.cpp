//
// Created by Alienson on 20.4.2024..
//

#include "GlBufferWrapper.h"

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
using namespace std;

GlBufferWrapper::~GlBufferWrapper() {

}

GlBufferWrapper::GlBufferWrapper(float *vertices, size_t length) : vb(vertices, length * sizeof(float)) {
    layout = VertexBufferLayout();
    layout.push<float>(2);
    layout.push<float>(2);
    va.addBuffer(vb, layout);
}

GlBufferWrapper::GlBufferWrapper(float *vertices, std::size_t length, VertexBufferLayout& layout) : vb(vertices, length * sizeof(float)) {
    this->layout = layout;
    va.addBuffer(vb, this->layout);
}
