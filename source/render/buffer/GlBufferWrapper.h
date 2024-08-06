//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_BUFFERDATA_H
#define INC_3DTEST_BUFFERDATA_H

#include <vector>
#include "VertexArray.h"

#include <memory>
#include <typeinfo>

class GlBufferWrapper{
public:
    GlBufferWrapper();
    ~GlBufferWrapper();
    GlBufferWrapper(float* vertices, std::size_t length);
    GlBufferWrapper(float* vertices, std::size_t length, std::vector<int>& layout);

    std::shared_ptr<VertexArray> va;
    std::shared_ptr<VertexBuffer> vb;
    std::shared_ptr<VertexBufferLayout> layout;
};

#endif //INC_3DTEST_BUFFERDATA_H