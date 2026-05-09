//
// Created by Alienso on 28.8.2024.
//

#ifndef RHYTHM_AXISALIGNEDBB_H
#define RHYTHM_AXISALIGNEDBB_H


#include "glm/vec2.hpp"

enum EnumSide{
    SIDE_TOP, SIDE_BOTTOM, SIDE_LEFT, SIDE_RIGHT, SIDE_NONE
};

class AxisAlignedBB {
public:
    AxisAlignedBB();
    AxisAlignedBB(glm::vec2 pos, glm::vec2 scale);
    AxisAlignedBB(float x1, float y1, float x2, float y2);

    [[nodiscard]] glm::vec2 getCenter() const;
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    void translate(glm::vec2 vec);
    void set(glm::vec2 pos, glm::vec2 scale);
    [[nodiscard]] bool intersects(AxisAlignedBB& other) const;

public:
    float minX;
    float minY;
    float maxX;
    float maxY;
};

class AxisAlignedHB : public AxisAlignedBB {
public:
    AxisAlignedHB();
    explicit AxisAlignedHB(float damage);
    AxisAlignedHB(glm::vec2 pos, glm::vec2 scale, float damage);
    AxisAlignedHB(float x1, float y1, float x2, float y2, float damage);

public:
    float damage = 0.0;
};


#endif //RHYTHM_AXISALIGNEDBB_H
