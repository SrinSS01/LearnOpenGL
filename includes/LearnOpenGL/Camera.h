//
// Created by Srinj on 6/12/2023.
//

#ifndef LEARNOPENGL_CAMERA_H
#define LEARNOPENGL_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
private:
    float yaw = -90.0f;
    float pitch = 0.0f;
    float speed = 6.0f;
    float sensitivity = 0.25f;
    float zoom = 45.0f;

    glm::vec3 position { 0.0f, 0.0f, 3.0f };
    glm::vec3 front { 0.0f, 0.0f, -1.0f };
    glm::vec3 up { 0.0f, 1.0f, 0.0f };

    glm::mat4 viewMatrix { glm::lookAt(position, position + front, up) };

public:
    [[nodiscard]] glm::mat4 const& getViewMatrix() const;
    void updateViewMatrix();
    void move(Direction direction, float deltaTime);
    void rotate(float xOffset, float yOffset);
    void Zoom(float yOffset);
    [[nodiscard]] float getZoom() const;
    glm::vec3 const& getPosition() const;
};

#endif //LEARNOPENGL_CAMERA_H
