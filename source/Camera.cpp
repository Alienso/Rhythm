//
// Created by Alienson on 16.4.2025.
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
        viewOffset.x -= (Global::player->pos().x - viewOffset.x) * (Global::player->pos().x - viewOffset.x) * Configuration::cameraFollowSpeed * deltaTime;
    } else if (Global::player->pos().x - viewOffset.x > Configuration::cameraDeadZone){
        viewOffset.x += (Global::player->pos().x - viewOffset.x) * (Global::player->pos().x - viewOffset.x) * Configuration::cameraFollowSpeed * deltaTime;
    }
    if (viewOffset.x != oldOffset) {
        Global::currentLevel->background.translate((viewOffset.x - oldOffset) * Configuration::cameraBackgroundSpeed);
    }
}

void Camera::setOffset(float x, float y) {
    viewOffset = {x, y};
}
