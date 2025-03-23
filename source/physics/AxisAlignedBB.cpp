//
// Created by Alienson on 28.8.2024..
//

#include "AxisAlignedBB.h"

AxisAlignedBB::AxisAlignedBB() : minX(0), minY(0), maxX(0), maxY(0) {

}


AxisAlignedBB::AxisAlignedBB(glm::vec2 pos, glm::vec2 scale) {
    minX = pos.x - scale.x / 2;
    minY = pos.y - scale.y / 2;
    maxX = pos.x + scale.x / 2;
    maxY = pos.y + scale.y / 2;
}

AxisAlignedBB::AxisAlignedBB(float x1, float y1, float x2, float y2) : minX(x1), minY(y1), maxX(x2), maxY(y2) {

}

bool AxisAlignedBB::intersects(AxisAlignedBB &other) const {
    return minX < other.maxX && maxX > other.minX && minY < other.maxY && maxY > other.minY;
}

void AxisAlignedBB::translate(glm::vec2 vec) {
    minX += vec.x;
    maxX += vec.x;
    minY += vec.y;
    maxY += vec.y;
}


//------HB


AxisAlignedHB::AxisAlignedHB() : AxisAlignedBB() {

}

AxisAlignedHB::AxisAlignedHB(float damage) : AxisAlignedBB(), damage(damage) {

}

AxisAlignedHB::AxisAlignedHB(glm::vec2 pos, glm::vec2 scale, float damage) : AxisAlignedBB(pos, scale), damage(damage) {

}

AxisAlignedHB::AxisAlignedHB(float x1, float y1, float x2, float y2, float damage) : AxisAlignedBB(x1, y1, x2, y2), damage(damage) {

}
