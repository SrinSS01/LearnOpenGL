//
// Created by Srinj on 6/5/2023.
//

#include "LearnOpenGL/GameEngine.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#include "LearnOpenGL/Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

using RawPtr = void*;

GameEngine::GameEngine():
windowManager(std::make_unique<WindowManager>(640, 480, "Game")),
camera(windowManager->getCamera()) {}

void GameEngine::run() {
    struct Vertex {
        struct Position {
            float x;
            float y;
            float z;
        } position;
        struct Normal {
            float x;
            float y;
            float z;
        } normal;
        struct Texture {
            float u;
            float v;
        } texture;
    };
    Vertex vertices[] = {
            Vertex::Position{-1.0f, -1.0f, -1.0f},  Vertex::Normal{0.0f,  0.0f, -1.0f}, Vertex::Texture{ 0.0f, 0.0f}, // Bottom-left
            Vertex::Position{ 1.0f, -1.0f, -1.0f},  Vertex::Normal{0.0f,  0.0f, -1.0f}, Vertex::Texture{ 1.0f, 0.0f}, // bottom-right
            Vertex::Position{ 1.0f,  1.0f, -1.0f},  Vertex::Normal{0.0f,  0.0f, -1.0f}, Vertex::Texture{ 1.0f, 1.0f}, // top-right
            Vertex::Position{ 1.0f,  1.0f, -1.0f},  Vertex::Normal{0.0f,  0.0f, -1.0f}, Vertex::Texture{ 1.0f, 1.0f}, // top-right
            Vertex::Position{-1.0f,  1.0f, -1.0f},  Vertex::Normal{0.0f,  0.0f, -1.0f}, Vertex::Texture{ 0.0f, 1.0f}, // top-left
            Vertex::Position{-1.0f, -1.0f, -1.0f},  Vertex::Normal{0.0f,  0.0f, -1.0f}, Vertex::Texture{ 0.0f, 0.0f}, // bottom-left

            Vertex::Position{ -1.0f, -1.0f,  1.0f},  Vertex::Normal{0.0f,  0.0f, 1.0f}, Vertex::Texture{0.0f, 0.0f}, // bottom-left
            Vertex::Position{  1.0f,  1.0f,  1.0f},  Vertex::Normal{0.0f,  0.0f, 1.0f}, Vertex::Texture{1.0f, 1.0f}, // top-right
            Vertex::Position{  1.0f, -1.0f,  1.0f},  Vertex::Normal{0.0f,  0.0f, 1.0f}, Vertex::Texture{1.0f, 0.0f}, // bottom-right
            Vertex::Position{  1.0f,  1.0f,  1.0f},  Vertex::Normal{0.0f,  0.0f, 1.0f}, Vertex::Texture{1.0f, 1.0f}, // top-right
            Vertex::Position{ -1.0f, -1.0f,  1.0f},  Vertex::Normal{0.0f,  0.0f, 1.0f}, Vertex::Texture{0.0f, 0.0f}, // bottom-left
            Vertex::Position{ -1.0f,  1.0f,  1.0f},  Vertex::Normal{0.0f,  0.0f, 1.0f}, Vertex::Texture{0.0f, 1.0f}, // top-left

            Vertex::Position{ -1.0f,  1.0f,  1.0f}, Vertex::Normal{-1.0f,  0.0f,  0.0f}, Vertex::Texture{1.0f, 0.0f}, // top-right
            Vertex::Position{ -1.0f, -1.0f, -1.0f}, Vertex::Normal{-1.0f,  0.0f,  0.0f}, Vertex::Texture{0.0f, 1.0f}, // bottom-left
            Vertex::Position{ -1.0f,  1.0f, -1.0f}, Vertex::Normal{-1.0f,  0.0f,  0.0f}, Vertex::Texture{1.0f, 1.0f}, // top-left
            Vertex::Position{ -1.0f, -1.0f, -1.0f}, Vertex::Normal{-1.0f,  0.0f,  0.0f}, Vertex::Texture{0.0f, 1.0f}, // bottom-left
            Vertex::Position{ -1.0f,  1.0f,  1.0f}, Vertex::Normal{-1.0f,  0.0f,  0.0f}, Vertex::Texture{1.0f, 0.0f}, // top-right
            Vertex::Position{ -1.0f, -1.0f,  1.0f}, Vertex::Normal{-1.0f,  0.0f,  0.0f}, Vertex::Texture{0.0f, 0.0f}, // bottom-right

            Vertex::Position{ 1.0f,  1.0f,  1.0f},  Vertex::Normal{1.0f,  0.0f,  0.0f}, Vertex::Texture{1.0f, 0.0f}, // top-left
            Vertex::Position{ 1.0f,  1.0f, -1.0f},  Vertex::Normal{1.0f,  0.0f,  0.0f}, Vertex::Texture{1.0f, 1.0f}, // top-right
            Vertex::Position{ 1.0f, -1.0f, -1.0f},  Vertex::Normal{1.0f,  0.0f,  0.0f}, Vertex::Texture{0.0f, 1.0f}, // bottom-right
            Vertex::Position{ 1.0f, -1.0f, -1.0f},  Vertex::Normal{1.0f,  0.0f,  0.0f}, Vertex::Texture{0.0f, 1.0f}, // bottom-right
            Vertex::Position{ 1.0f, -1.0f,  1.0f},  Vertex::Normal{1.0f,  0.0f,  0.0f}, Vertex::Texture{0.0f, 0.0f}, // bottom-left
            Vertex::Position{ 1.0f,  1.0f,  1.0f},  Vertex::Normal{1.0f,  0.0f,  0.0f}, Vertex::Texture{1.0f, 0.0f}, // top-left

            Vertex::Position{-1.0f, -1.0f, -1.0f},  Vertex::Normal{0.0f, -1.0f,  0.0f},Vertex::Texture{ 0.0f, 1.0f}, // top-right
            Vertex::Position{ 1.0f, -1.0f,  1.0f},  Vertex::Normal{0.0f, -1.0f,  0.0f},Vertex::Texture{ 1.0f, 0.0f}, // bottom-left
            Vertex::Position{ 1.0f, -1.0f, -1.0f},  Vertex::Normal{0.0f, -1.0f,  0.0f},Vertex::Texture{ 1.0f, 1.0f}, // top-left
            Vertex::Position{ 1.0f, -1.0f,  1.0f},  Vertex::Normal{0.0f, -1.0f,  0.0f},Vertex::Texture{ 1.0f, 0.0f}, // bottom-left
            Vertex::Position{-1.0f, -1.0f, -1.0f},  Vertex::Normal{0.0f, -1.0f,  0.0f},Vertex::Texture{ 0.0f, 1.0f}, // top-right
            Vertex::Position{-1.0f, -1.0f,  1.0f},  Vertex::Normal{0.0f, -1.0f,  0.0f},Vertex::Texture{ 0.0f, 0.0f}, // bottom-right

            Vertex::Position{-1.0f,  1.0f, -1.0f},  Vertex::Normal{0.0f,  1.0f,  0.0f}, Vertex::Texture{0.0f, 1.0f}, // top-left
            Vertex::Position{ 1.0f,  1.0f, -1.0f},  Vertex::Normal{0.0f,  1.0f,  0.0f}, Vertex::Texture{1.0f, 1.0f}, // top-right
            Vertex::Position{ 1.0f,  1.0f,  1.0f},  Vertex::Normal{0.0f,  1.0f,  0.0f}, Vertex::Texture{1.0f, 0.0f}, // bottom-right
            Vertex::Position{ 1.0f,  1.0f,  1.0f},  Vertex::Normal{0.0f,  1.0f,  0.0f}, Vertex::Texture{1.0f, 0.0f}, // bottom-right
            Vertex::Position{-1.0f,  1.0f,  1.0f},  Vertex::Normal{0.0f,  1.0f,  0.0f}, Vertex::Texture{0.0f, 0.0f}, // bottom-left
            Vertex::Position{-1.0f,  1.0f, -1.0f},  Vertex::Normal{0.0f,  1.0f,  0.0f}, Vertex::Texture{0.0f, 1.0f}  // top-left
    };

    GLuint vbo, vao[2];
    glGenVertexArrays(1, &vao[0]);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
    glBindVertexArray(vao[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), RawPtr (offsetof(Vertex, position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), RawPtr (offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), RawPtr (offsetof(Vertex, texture)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glGenVertexArrays(1, &vao[1]);
    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), RawPtr (offsetof(Vertex, position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), RawPtr (offsetof(Vertex, texture)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Shader objectShader("resources/shaders/object.vs", "resources/shaders/object.fs");
    Shader lampShader("resources/shaders/lamp.vs", "resources/shaders/lamp.fs");

    GLuint lampTex = load_texture("resources/textures/redstone_lamp_on.png", GL_TEXTURE0);
    GLuint diffuseMap = load_texture("resources/textures/container2.png", GL_TEXTURE0);
    GLuint specularMap = load_texture("resources/textures/lighting_maps_specular_color.png", GL_TEXTURE1);

    glm::vec3 lightPos(2.2f, 2.0f, 3.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

//    float radius = glm::length(lightPos);

    float deltaTime;
    float lastFrame = 0.0f;
//    double alpha = 0, theta = 0;
    while (!windowManager->shouldClose()) {
        /*theta += 1.1;
        if (alpha > 360) alpha = 0;
        if (theta > 360) {
            theta = 0;
            alpha += 1.1;
        }

        lightPos.x = GLfloat (radius * glm::cos(glm::radians(alpha)) * glm::sin(glm::radians(theta)));
        lightPos.z = GLfloat (radius * glm::cos(glm::radians(theta)));
        lightPos.y = GLfloat (radius * glm::sin(glm::radians(alpha)) * glm::sin(glm::radians(theta)));*/

        glm::mat4 projection = windowManager->getProjectionMatrix();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        auto currentFrame = GLfloat (glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        windowManager->pollEvents();
        handleInput(deltaTime);
        windowManager->clearScreen();
        auto& viewPos = camera.getPosition();
        objectShader.use();
        objectShader.setUniformMat4f("uProjection", glm::value_ptr(projection));
        objectShader.setUniformMat4f("uView", glm::value_ptr(view));
        objectShader.setUniformMat4f("uModel", glm::value_ptr(model));
        objectShader.setUniform3f("uViewPos", viewPos.x, viewPos.y, viewPos.z);

        objectShader.setUniform1f("uMaterial.shininess", 64.0f);
        objectShader.setUniform1i("uMaterial.diffuse", 0);
        objectShader.setUniform1i("uMaterial.specular", 1);

        objectShader.setUniform3f("uLight.ambient", 0.2f, 0.2f, 0.2f);
        objectShader.setUniform3f("uLight.diffuse", 0.5f, 0.5f, 0.5f);
        objectShader.setUniform3f("uLight.specular", 1.0f, 1.0f, 1.0f);
        objectShader.setUniform3f("uLight.position", lightPos.x, lightPos.y, lightPos.z);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, sizeof vertices / sizeof vertices[0]);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        lampShader.use();
        lampShader.setUniformMat4f("uProjection", glm::value_ptr(projection));
        lampShader.setUniformMat4f("uView", glm::value_ptr(view));
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.5f));
        lampShader.setUniformMat4f("uModel", glm::value_ptr(model));
        lampShader.setUniform3f("uLampColor", lightColor.r, lightColor.g, lightColor.b);
        lampShader.setUniform1i("uTexture", 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, lampTex);
        glBindVertexArray(vao[1]);
        glDrawArrays(GL_TRIANGLES, 0, sizeof vertices / sizeof vertices[0]);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        windowManager->swapBuffers();
    }
}

GLuint GameEngine::load_texture(const char *path, int slot) {
    int width, height, nrChannels;
    unsigned char* textureData = stbi_load(path, &width, &height, &nrChannels, 0);
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (textureData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(textureData);
    return texture;
}

void GameEngine::handleInput(GLfloat deltaTime) {
    if (Callbacks::Keyboard::isKeyPressed(GLFW_KEY_ESCAPE)) {
        windowManager->closeWindow();
    }
    if (Callbacks::Keyboard::isKeyPressed(GLFW_KEY_F11)) {
        windowManager->toggleFullscreen();
        Callbacks::Keyboard::setKeyPressed(GLFW_KEY_F11, false);
    }
    if (Callbacks::Keyboard::isKeyPressed(GLFW_KEY_F10)) {
        windowManager->toggleMouseCapture();
        Callbacks::Keyboard::setKeyPressed(GLFW_KEY_F10, false);
    }
    if (Callbacks::Keyboard::isKeyPressed(GLFW_KEY_W)) {
        camera.move(Direction::FORWARD, deltaTime);
    }
    if (Callbacks::Keyboard::isKeyPressed(GLFW_KEY_S)) {
        camera.move(Direction::BACKWARD, deltaTime);
    }
    if (Callbacks::Keyboard::isKeyPressed(GLFW_KEY_A)) {
        camera.move(Direction::LEFT, deltaTime);
    }
    if (Callbacks::Keyboard::isKeyPressed(GLFW_KEY_D)) {
        camera.move(Direction::RIGHT, deltaTime);
    }
    if (Callbacks::Keyboard::isKeyPressed(GLFW_KEY_SPACE)) {
        camera.move(Direction::UP, deltaTime);
    }
    if (Callbacks::Keyboard::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        camera.move(Direction::DOWN, deltaTime);
    }
}

#pragma clang diagnostic pop