//
// Created by Srinj on 6/25/2023.
//

#ifndef LEARNOPENGL_CURSORPOS_H
#define LEARNOPENGL_CURSORPOS_H

#include "LearnOpenGL/WindowManager.h"
#include "LearnOpenGL/callbacks/Callbacks.h"

namespace Callbacks {
    class CursorPos : public Callback {
    public:
        explicit CursorPos(GLFWwindow * window, WindowManager::WindowCache cache);
        ~CursorPos();
        void create(WindowManager* windowManager);

    private:
        static bool firstMouse;
        static GLdouble lastX;
        static GLdouble lastY;
    };
}

#endif //LEARNOPENGL_CURSORPOS_H
