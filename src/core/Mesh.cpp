//
// Created by Srinj on 7/2/2023.
//

#include "LearnOpenGL/Mesh.h"

Mesh::Mesh(std::vector<Vertex> *vertices, std::vector<GLuint> *indices, std::vector<Texture> *textures):
vertices(vertices), indices(indices), textures(textures), VAO(0), VBO(0), EBO(0) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
            GL_ARRAY_BUFFER,
            GLsizeiptr (vertices->size() * sizeof(Vertex)),
            &vertices->operator[](0),
            GL_STATIC_DRAW
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            GLsizeiptr (indices->size() * sizeof(GLuint)),
            &indices->operator[](0),
            GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (GLvoid*) offsetof(Vertex, position)
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (GLvoid*) offsetof(Vertex, normal)
    );
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (GLvoid*) offsetof(Vertex, texCoords)
    );
    glBindVertexArray(0);
}

void Mesh::draw(Shader &shader) const {
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for (GLuint i = 0; i < textures->size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::stringstream ss;
        std::string number;
        std::string type = textures->operator[](i).type;

        if (type == "texture_diffuse") {
            ss << diffuseNr++;
        } else if (type == "texture_specular") {
            ss << specularNr++;
        }

        number = ss.str();
        shader.setUniform1i((type + number).c_str(), GLint(i));
        glBindTexture(GL_TEXTURE_2D, textures->operator[](i).id);
    }
    shader.setUniform1f("uMaterial.shininess", 16.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, GLint (indices->size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    for (int i = 0; i < textures->size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
