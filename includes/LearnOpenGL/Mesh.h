//
// Created by Srinj on 7/2/2023.
//

#ifndef LEARNOPENGL_MESH_H
#define LEARNOPENGL_MESH_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/types.h>

#include "LearnOpenGL/Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    GLuint id;
    std::string type;
    aiString path;
};

class Mesh {
public:
    std::vector<Vertex>* vertices;
    std::vector<GLuint>* indices;
    std::vector<Texture>* textures;

public:
    Mesh(std::vector<Vertex>* vertices, std::vector<GLuint>* indices, std::vector<Texture>* textures);

    void draw(Shader& shader) const;

private:
    GLuint VAO, VBO, EBO;
};

#endif //LEARNOPENGL_MESH_H
