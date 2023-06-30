//
// Created by Srinj on 6/5/2023.
//
#include "LearnOpenGL/WindowManagerHeader.h"
#include "LearnOpenGL/WindowManager.h"

#include <iostream>

const float Z_NEAR = 0.1f;
const float Z_FAR = 1000.0f;

WindowManager::WindowManager(int width, int height, const char *title, bool vsync) :
        windowCache{width, height, 0, 0, width, height},
        projectionMatrix(glm::perspective(camera.getZoom(), float(width) / float(height), Z_NEAR, Z_FAR)) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    errorCallback = std::make_unique<Callbacks::Error>();
    keyboardCallback = std::make_unique<Callbacks::Keyboard>(window);
    windowSizeCallback = std::make_unique<Callbacks::WindowSize>(window);
    cursorPosCallback = std::make_unique<Callbacks::CursorPos>(window, windowCache);
    keyboardCallback->create();
    windowSizeCallback->create(this);
    errorCallback->create();
    cursorPosCallback->create(this);
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");
    }
    if (vsync) {
        glfwSwapInterval(1);
    }
    auto *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if (videoMode) {
        glfwSetWindowPos(window, (videoMode->width - width) / 2, (videoMode->height - height) / 2);
    }
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_STENCIL_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CW);
    glfwShowWindow(window);
    toggleMouseCapture();
}

WindowManager::~WindowManager() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void WindowManager::swapBuffers() {
    glfwSwapBuffers(window);
}

void WindowManager::pollEvents() {
    glfwPollEvents();
}

bool WindowManager::shouldClose() {
    return glfwWindowShouldClose(window);
}

void WindowManager::clearScreen() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::toggleMouseCapture() {
    mouseCaptured = !mouseCaptured;
    glfwSetInputMode(window, GLFW_CURSOR, mouseCaptured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void WindowManager::closeWindow() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void WindowManager::toggleFullscreen() {
    auto *monitor = glfwGetPrimaryMonitor();
    auto *vidMode = glfwGetVideoMode(monitor);
    if (vidMode) {
        if (glfwGetWindowMonitor(window)) {
            // set window to windowed mode
            glfwSetWindowMonitor(window, nullptr, windowCache.x, windowCache.y, windowCache.oldWidth,
                                 windowCache.oldHeight, vidMode->refreshRate);
            glfwSwapInterval(1);
        } else {
            // save old window dimensions
            glfwGetWindowPos(window, &windowCache.x, &windowCache.y);
            glfwGetWindowSize(window, &windowCache.oldWidth, &windowCache.oldHeight);

            // set window to monitor
            glfwSetWindowMonitor(window, monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
            glfwSwapInterval(1);
        }
        windowCache.isWindowModeChanged = true;
    }
}

void WindowManager::updateProjectionMatrix() {
    float aspectRatio = float(windowCache.newWidth) / float(windowCache.newHeight);
    projectionMatrix = glm::perspective(camera.getZoom(), aspectRatio, Z_NEAR, Z_FAR);
}

glm::mat4 const &WindowManager::getProjectionMatrix() const {
    return projectionMatrix;
}

Camera &WindowManager::getCamera() {
    return camera;
}
