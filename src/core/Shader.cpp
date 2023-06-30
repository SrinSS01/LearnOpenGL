//
// Created by Srinj on 6/25/2023.
//

#include "LearnOpenGL/Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

std::string parseShader(const char *path) {
    // open file from path and read it's contents
    std::ifstream shaderFile;
    shaderFile.open(path);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

GLuint compileShader(GLenum shaderType, const char *shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    // check for errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::" << (shaderType == GL_VERTEX_SHADER? "VERTEX SHADER": "FRAGMENT SHADER") << "::COMPILATION_FAILED\n" << infoLog << "\n";
        return 0;
    }
    return shader;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath):
program(glCreateProgram()) {
    std::string vertexCode = parseShader(vertexPath);
    std::string fragmentCode = parseShader(fragmentPath);
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    // check for errors
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }
    glValidateProgram(program);
    // check for errors
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::VALIDATION_FAILED\n" << infoLog << "\n";
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(program);
}

void Shader::use() const {
    glUseProgram(program);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::setUniform1i(const char *name, int value) const {
    glUniform1i(glGetUniformLocation(program, name), value);
}

void Shader::setUniform1f(const char *name, float value) const {
    glUniform1f(glGetUniformLocation(program, name), value);
}

void Shader::setUniform3f(const char *name, float v1, float v2, float v3) const {
    glUniform3f(glGetUniformLocation(program, name), v1, v2, v3);
}

void Shader::setUniformMat4f(const char *name, float *matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, matrix);
}

