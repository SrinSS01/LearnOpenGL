//
// Created by Srinj on 6/9/2023.
//

#ifndef LEARNOPENGL_WINDOWSIZE_H
#define LEARNOPENGL_WINDOWSIZE_H

#include "LearnOpenGL/WindowManager.h"
#include "LearnOpenGL/callbacks/Callbacks.h"

namespace Callbacks {
    class WindowSize : public Callback {
    public:
        WindowSize() = default;
        explicit WindowSize(GLFWwindow* window) : Callback(window) {}
        ~WindowSize();
        void create(WindowManager* windowManager);

    private:
    };
}

#endif //LEARNOPENGL_WINDOWSIZE_H
