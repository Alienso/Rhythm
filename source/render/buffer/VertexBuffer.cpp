//
// Created by Alienso on 19.9.2022..
//

#include "VertexBuffer.h"

#include "glad/glad.h"

VertexBuffer::VertexBuffer() {

}

void VertexBuffer::initialize(const void *data, unsigned int size) {
    glGenBuffers(1, &rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    if (rendererID != (unsigned int)-1)
        glDeleteBuffers(1, &rendererID);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}





