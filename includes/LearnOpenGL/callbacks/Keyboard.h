//
// Created by Srinj on 6/9/2023.
//

#ifndef LEARNOPENGL_KEYBOARD_H
#define LEARNOPENGL_KEYBOARD_H

#include "LearnOpenGL/callbacks/Callbacks.h"

namespace Callbacks {
    class Keyboard : public Callback {
    public:
        Keyboard() = default;
        explicit Keyboard(GLFWwindow* window) : Callback(window) {}
        ~Keyboard();
        void create() override;
        static void setKeyPressed(int keyCode, bool isPressed);
        static bool isKeyPressed(int keyCode);
    private:
        static bool keys[GLFW_KEY_LAST];
    };
}

#endif //LEARNOPENGL_KEYBOARD_H
