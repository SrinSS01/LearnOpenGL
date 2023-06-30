//
// Created by Srinj on 6/8/2023.
//

#define KEY_CALLBACK

#include "LearnOpenGL/callbacks/Keyboard.h"

bool Callbacks::Keyboard::keys[GLFW_KEY_LAST] {};

void Callbacks::Keyboard::create() {
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == -1) {
            return;
        }
        setKeyPressed(key, action == GLFW_PRESS || action == GLFW_REPEAT);
    });
}

void Callbacks::Keyboard::setKeyPressed(int keyCode, bool isPressed) {
    keys[keyCode] = isPressed;
}

bool Callbacks::Keyboard::isKeyPressed(int keyCode) {
    return keys[keyCode];
}

Callbacks::Keyboard::~Keyboard() {
    glfwSetKeyCallback(window, nullptr);
}
