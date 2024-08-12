//
// Created by Alienson on 21.4.2024..
//

#ifndef VOXEL_INPUTHANDLER_H
#define VOXEL_INPUTHANDLER_H


class GLFWwindow;
class Rhythm;

class InputHandler {
public:
    explicit InputHandler(Rhythm* app) : app(app){}
    void processMouseInput();
    void processMouseClickInput();
    void processKeyboardInput(double deltaTime);

private:
    Rhythm* app;
};


#endif //VOXEL_INPUTHANDLER_H
