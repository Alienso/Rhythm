//
// Created by Alienson on 6.9.2024..
//

#ifndef RHYTHM_GLBUFFERWRAPPERINSTANCED_H
#define RHYTHM_GLBUFFERWRAPPERINSTANCED_H

#include <vector>
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "glm/fwd.hpp"

#include <memory>
#include <typeinfo>

class GlBufferWrapperInstanced {
public:
    GlBufferWrapperInstanced();
    void initialize(std::vector<glm::fvec2>& offsets, float scale);

    VertexArray va;
    VertexBuffer quadVb;
    VertexBuffer instanceVb;
    VertexBufferLayout quadLayout;
    VertexBufferLayout instanceLayout;
};


#endif //RHYTHM_GLBUFFERWRAPPERINSTANCED_H
