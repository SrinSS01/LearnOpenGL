//
// Created by Srinj on 7/2/2023.
//

#ifndef LEARNOPENGL_MODEL_H
#define LEARNOPENGL_MODEL_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "LearnOpenGL/Mesh.h"

GLuint TextureFromFile(const std::string& path, const std::string& directory);

class Model {
public:
    explicit Model(const std::string& path);

    void draw(Shader& shader) const;

private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> texturesLoaded;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
};

#endif //LEARNOPENGL_MODEL_H
