//
// Created by Alienso on 19.9.2022..
//

#ifndef GRASSTERRAIN_VERTEXBUFFER_H
#define GRASSTERRAIN_VERTEXBUFFER_H


class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();

    void initialize(const void *data, unsigned int size);

    void bind() const;
    void unbind() const;

private:
    unsigned int rendererID = -1;
};


#endif //GRASSTERRAIN_VERTEXBUFFER_H
