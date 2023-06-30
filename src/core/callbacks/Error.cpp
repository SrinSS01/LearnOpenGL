//
// Created by Srinj on 6/9/2023.
//

#include "LearnOpenGL/callbacks/Error.h"
#include <iostream>

Callbacks::Error::~Error() {
    glfwSetErrorCallback(nullptr);
}

void Callbacks::Error::create() {
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "Error: [" << error << "]: " << description << std::endl;
    });
}
