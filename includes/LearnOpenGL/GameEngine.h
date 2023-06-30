//
// Created by Srinj on 6/5/2023.
//

#ifndef LEARNOPENGL_GAMEENGINE_H
#define LEARNOPENGL_GAMEENGINE_H

#include "LearnOpenGL/WindowManager.h"
#include "callbacks/Keyboard.h"
#include "LearnOpenGL/Camera.h"
#include <memory>

class GameEngine {
public:
    GameEngine();
    void run();
    void handleInput(GLfloat deltaTime);
private:
    const std::unique_ptr<WindowManager> windowManager;
    Camera& camera;

    static GLuint load_texture(const char *path, int slot) ;
};

#endif //LEARNOPENGL_GAMEENGINE_H
