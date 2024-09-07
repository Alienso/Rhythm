//
// Created by Alienso on 19.9.2022..
//

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include <cassert>

using namespace std;

VertexArray::VertexArray() {
    glGenVertexArrays(1,&rendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1,&rendererID);
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    this->bind();
    vb.bind();

    const std::vector<VertexBufferElement>& elements = layout.getElements();
    size_t offset = 0;

    for (size_t i=0; i<elements.size(); i++){
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset+=element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::addInstanceBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout, const int index) {
    assert(layout.getElements().size() == 1);
    this->bind();
    vb.bind();

    const auto& element = layout.getElements()[0];
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, element.count, element.type, element.normalized, layout.getStride(), (const void*)nullptr);
    glVertexAttribDivisor(index, element.divisor);
}


void VertexArray::bind() const {
    glBindVertexArray(rendererID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}