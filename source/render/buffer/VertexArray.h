//
// Created by Alienso on 19.9.2022..
//

#ifndef GRASSTERRAIN_VERTEXARRAY_H
#define GRASSTERRAIN_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexBufferLayout;

class VertexArray {

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void addInstanceBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, int index);
    void bind() const;
    void unbind() const;

private:
    unsigned int rendererID;
};


#endif //GRASSTERRAIN_VERTEXARRAY_H
