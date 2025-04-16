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
    float oldOffset = viewOffset.x;
    if (Global::player->pos().x - viewOffset.x < -Configuration::cameraDeadZone){
        viewOffset.x = Global::player->pos().x + Configuration::cameraDeadZone;
    } else if (Global::player->pos().x - viewOffset.x > Configuration::cameraDeadZone){
        viewOffset.x = Global::player->pos().x - Configuration::cameraDeadZone;
    }
    if (viewOffset.x != oldOffset) {
        Global::currentLevel->background.translate((viewOffset.x - oldOffset) * 0.1f);
    }
}

void Camera::setOffset(float x, float y) {
    viewOffset = {x, y};
}
