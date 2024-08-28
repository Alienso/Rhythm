//
// Created by Alienson on 28.8.2024..
//

#ifndef RHYTHM_AXISALIGNEDBB_H
#define RHYTHM_AXISALIGNEDBB_H


#include "glm/vec2.hpp"

class AxisAlignedBB {
public:
    AxisAlignedBB();
    AxisAlignedBB(glm::vec2 pos, glm::vec2 scale);
    AxisAlignedBB(float x1, float y1, float x2, float y2);

    void translate(glm::vec2 vec);
    [[nodiscard]] bool intersects(AxisAlignedBB& other) const;

private:
    float minX,minY,maxX,maxY;
};


#endif //RHYTHM_AXISALIGNEDBB_H
