//
// Created by Srinj on 6/9/2023.
//

#include "LearnOpenGL/callbacks/WindowSize.h"

void Callbacks::WindowSize::create(WindowManager* windowManager) {
    static WindowManager* windowManagerStatic = windowManager;
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        windowManagerStatic->windowCache.newWidth = width;
        windowManagerStatic->windowCache.newHeight = height;
        windowManagerStatic->updateProjectionMatrix();
        glViewport(0, 0, width, height);
    });
}

Callbacks::WindowSize::~WindowSize() {
    glfwSetWindowSizeCallback(window, nullptr);
}