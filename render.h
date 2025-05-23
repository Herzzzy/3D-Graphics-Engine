#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Render {
public:
    Render(const std::vector<float>& vertices,
           const std::vector<unsigned int>& indices,
           const std::vector<float>& color,
           unsigned int textureID = 0);
    
    ~Render();
    void Draw(const glm::mat4& mvp);

private:
    GLuint VAO, VBO, EBO;
    GLuint shaderProgram;
    int vertexCount;
    std::vector<float> color;
    unsigned int textureID;
};