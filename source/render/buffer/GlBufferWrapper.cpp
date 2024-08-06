//
// Created by Alienson on 20.4.2024..
//

#include "GlBufferWrapper.h"

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
using namespace std;

GlBufferWrapper::GlBufferWrapper() {
    vb = nullptr;
    layout = nullptr;
    va = nullptr;
}

GlBufferWrapper::~GlBufferWrapper() {

}


GlBufferWrapper::GlBufferWrapper(float *vertices, size_t length) {
    vb = make_shared<VertexBuffer>(vertices, length * sizeof(float));
    layout = make_shared<VertexBufferLayout>();
    layout->push<float>(2);
    layout->push<float>(2);
    va = make_shared<VertexArray>();
    va->addBuffer(*vb, *layout);
}

GlBufferWrapper::GlBufferWrapper(float *vertices, std::size_t length, std::vector<int>& layoutFormat) {
    vb = make_shared<VertexBuffer>(vertices, length * sizeof(float));
    layout = make_shared<VertexBufferLayout>();

    for (int i : layoutFormat){
        layout->push<float>(i);
    }

    va = make_shared<VertexArray>();
    va->addBuffer(*vb, *layout);
}
