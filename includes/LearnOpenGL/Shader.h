//
// Created by Srinj on 6/25/2023.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use() const;
    void unbind();
    void setUniform1i(const char* name, int value) const;
    void setUniform1f(const char* name, float value) const;
    void setUniform3f(const char* name, float v1, float v2, float v3) const;
    void setUniformMat4f(const char* name, float *matrix) const;

private:
    unsigned int program;
};

#endif //LEARNOPENGL_SHADER_H
