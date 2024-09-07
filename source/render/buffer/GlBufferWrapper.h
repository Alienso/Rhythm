//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_BUFFERDATA_H
#define INC_3DTEST_BUFFERDATA_H

#include <vector>
#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include <memory>
#include <typeinfo>

class GlBufferWrapper{
public:
    GlBufferWrapper(float* vertices, std::size_t length);

    VertexArray va;
    VertexBuffer vb;
    VertexBufferLayout layout;
};

#endif //INC_3DTEST_BUFFERDATA_H