//
// Created by Srinj on 6/5/2023.
//

#ifndef LEARNOPENGL_CALLBACKS_H
#define LEARNOPENGL_CALLBACKS_H
#include "GLFW/glfw3.h"

namespace Callbacks {
    class Callback {
    public:
        Callback() = default;
        explicit Callback(GLFWwindow* window) : window(window) {}
        ~Callback() = default;
        virtual void create() {};

    protected:
        GLFWwindow *window { nullptr };
    };
} // Callbacks

#endif //LEARNOPENGL_CALLBACKS_H
