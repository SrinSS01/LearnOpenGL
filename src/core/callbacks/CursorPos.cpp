//
// Created by Srinj on 6/25/2023.
//

#include "LearnOpenGL/callbacks/CursorPos.h"
#include <iostream>

bool Callbacks::CursorPos::firstMouse = true;
GLdouble Callbacks::CursorPos::lastX = 0;
GLdouble Callbacks::CursorPos::lastY = 0;

Callbacks::CursorPos::CursorPos(GLFWwindow* window, WindowManager::WindowCache cache): Callback(window) {
    lastX = cache.oldWidth / 2.0;
    lastY = cache.oldHeight / 2.0;
}

Callbacks::CursorPos::~CursorPos() {
    glfwSetCursorPosCallback(window, nullptr);
}

void Callbacks::CursorPos::create(WindowManager* windowManager) {
    auto& camera = windowManager->getCamera();
    static Camera* sCamera = &camera;
    static auto sWindowManager = windowManager;
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        if (sWindowManager->windowCache.isWindowModeChanged) {
            lastX = xpos;
            lastY = ypos;
            sWindowManager->windowCache.isWindowModeChanged = false;
            return;
        }
        if (!sWindowManager->mouseCaptured) {
            return;
        }
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        auto xoffset = xpos - lastX;
        auto yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        sCamera->rotate(GLfloat (xoffset), GLfloat (yoffset));
    });
}
