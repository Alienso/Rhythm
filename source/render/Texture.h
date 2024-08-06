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

    Texture();
    Texture(const char* path, int type);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

private:
    std::string filePath;
    int width, height, bytesPerPixel;
};


#endif //GRASSTERRAIN_TEXTURE_H
