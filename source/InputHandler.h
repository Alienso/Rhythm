//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_INPUTHANDLER_H
#define VOXEL_INPUTHANDLER_H

class GLFWwindow;

class InputHandler {
public:
    explicit InputHandler(GLFWwindow* window) : window(window){}
    void processMouseInput();
    void processKeyboardInput(double deltaTime);

private:
    GLFWwindow* window = nullptr;
};


#endif //VOXEL_INPUTHANDLER_H
