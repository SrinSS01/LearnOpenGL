//
// Created by Srinj on 6/12/2023.
//

#include "LearnOpenGL/Camera.h"

glm::mat4 const& Camera::getViewMatrix() const {
    return viewMatrix;
}

void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(position, position + front, up);
}

void Camera::move(Direction direction, float deltaTime) {
    float velocity = speed * deltaTime;
    switch (direction) {
        case FORWARD:
            position += front * velocity;
            break;
        case BACKWARD:
            position -= front * velocity;
            break;
        case LEFT:
            position -= glm::normalize(glm::cross(front, up)) * velocity;
            break;
        case RIGHT:
            position += glm::normalize(glm::cross(front, up)) * velocity;
            break;
        case UP:
            position += up * velocity;
            break;
        case DOWN:
            position -= up * velocity;
            break;
    }
    updateViewMatrix();
}

void Camera::rotate(float xOffset, float yOffset) {
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    front.x = float(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    front.y = float(sin(glm::radians(pitch)));
    front.z = float(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
    front = glm::normalize(front);
    updateViewMatrix();
}

void Camera::Zoom(float yOffset) {
    if (zoom >= 1.0f && zoom <= 45.0f) {
        zoom -= yOffset * 0.05f;
    }
    if (zoom <= 1.0f) {
        zoom = 1.0f;
    }
    if (zoom >= 45.0f) {
        zoom = 45.0f;
    }
}

float Camera::getZoom() const {
    return zoom;
}

glm::vec3 const &Camera::getPosition() const {
    return position;
}
