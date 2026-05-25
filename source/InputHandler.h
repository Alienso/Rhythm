//
// Created by Alienso on 21.4.2024.
//

#ifndef VOXEL_INPUTHANDLER_H
#define VOXEL_INPUTHANDLER_H


#include <glm/vec2.hpp>

class GLFWwindow;
class Rhythm;

class InputHandler {
public:
    explicit InputHandler(Rhythm* app) : app(app){}
    void processMouseInput();
    void processMouseClickInput();
    void processKeyboardInput(double deltaTime);

    glm::vec2 previousCursorPos = {0,0}; //Temp move to private

private:
    Rhythm* app;

};


#endif //VOXEL_INPUTHANDLER_H
