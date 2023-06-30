//
// Created by Srinj on 6/5/2023.
//

#ifndef LEARNOPENGL_WINDOWMANAGER_H
#define LEARNOPENGL_WINDOWMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <glm/glm.hpp>
#include "LearnOpenGL/Camera.h"

namespace Callbacks {
    class Keyboard;
    class WindowSize;
    class Error;
    class CursorPos;
}

class WindowManager {
public:
    struct WindowCache {
        int oldWidth{};
        int oldHeight{};
        int x{};
        int y{};
        int newWidth{};
        int newHeight{};
        bool isWindowModeChanged {false };
    };
public:
    WindowManager(int width, int height, const char* title, bool vsync = true);
    ~WindowManager();
    void swapBuffers();
    static void pollEvents();
    bool shouldClose();
    static void clearScreen();
    void toggleMouseCapture();
    void closeWindow();
    void toggleFullscreen();
    void updateProjectionMatrix();
    [[nodiscard]] glm::mat4 const& getProjectionMatrix() const;
    Camera& getCamera();
private:
    GLFWwindow* window;
    Camera camera {};
    std::unique_ptr<Callbacks::Keyboard> keyboardCallback;
    std::unique_ptr<Callbacks::WindowSize> windowSizeCallback;
    std::unique_ptr<Callbacks::Error> errorCallback;
    std::unique_ptr<Callbacks::CursorPos> cursorPosCallback;
    glm::mat4 projectionMatrix;
public:
    WindowCache windowCache{};
    bool mouseCaptured = false;
};


#endif //LEARNOPENGL_WINDOWMANAGER_H
