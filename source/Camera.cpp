//
// Created by Alienson on 16.4.2025..
//

#include "Camera.h"
#include "reference/Global.h"

Camera::Camera() {

}

const glm::vec2 &Camera::getOffset() const {
    return viewOffset;
}

void Camera::onUpdate(float deltaTime) {
    viewOffset.x = Global::player->pos.x;
}

void Camera::setOffset(float x, float y) {
    viewOffset = {x, y};
}
