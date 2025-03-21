//
// Created by Alienso on 19.9.2022..
//

#ifndef GRASSTERRAIN_VERTEXBUFFERLAYOUT_H
#define GRASSTERRAIN_VERTEXBUFFERLAYOUT_H

#include "glad/glad.h"

#include <vector>
#include <typeinfo>

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;
    unsigned int divisor;

    static unsigned int getSizeOfType(unsigned int type);
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
public:
    [[nodiscard]] unsigned int getStride() const;

public:
    VertexBufferLayout();

    template<typename T>
    void push(unsigned int count, unsigned int divisor = 0){
        if (typeid(T) == typeid(float)){
            elements.push_back({GL_FLOAT, count, GL_FALSE, divisor});
            stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
        }
        if (typeid(T) == typeid(unsigned int)){
            elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE, divisor});
            stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
        }
        if (typeid(T) == typeid(unsigned char)){
            elements.push_back({GL_UNSIGNED_BYTE,count,GL_TRUE, divisor});
            stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
        }
    }

    [[nodiscard]] const std::vector<VertexBufferElement> &getElements() const;
};


#endif //GRASSTERRAIN_VERTEXBUFFERLAYOUT_H
