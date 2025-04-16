//
// Created by Alienson on 16.4.2025..
//

#ifndef RHYTHM_CAMERA_H
#define RHYTHM_CAMERA_H


#include <glm/vec2.hpp>

class Camera {

public:
    Camera();

    [[nodiscard]] const glm::vec2& getOffset() const;

private:
    glm::vec2 viewOffset = {0,0};
};


#endif //RHYTHM_CAMERA_H
