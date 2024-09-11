//
// Created by Alienso on 19.9.2022..
//

#ifndef GRASSTERRAIN_TEXTURE_H
#define GRASSTERRAIN_TEXTURE_H

#include <string>
#include <vector>

class Texture {
public:
    unsigned int ID;
    unsigned int rendererID;

    explicit Texture(unsigned int id);
    Texture(unsigned int id, const char* path, int type);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    int width, height, bytesPerPixel;

private:
    std::string filePath;
};


#endif //GRASSTERRAIN_TEXTURE_H
