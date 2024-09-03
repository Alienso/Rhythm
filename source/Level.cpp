//
// Created by Alienson on 1.8.2024..
//

#include "Level.h"
#include "reference/Reference.h"

Level::Level() {
}

void Level::onRender() {
    background.onRender();
}

void Level::onUpdate(float deltaTime) {
    background.translate(0.1f * deltaTime);
}
