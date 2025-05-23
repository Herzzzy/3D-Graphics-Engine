#pragma once

#include "render.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

extern float xyRelation;

class Utility {
    protected:
        std::vector<std::shared_ptr<Render>> faces;
        virtual void updateVertices() = 0;
    
    public:
        Utility(float x, float y, float z);
        void Move(float dx, float dy, float dz);
        virtual void Draw(const glm::mat4& mvp);
        virtual void Rebuild() { updateVertices(); }
        float x, y, z;
};

extern std::vector<Utility*> gameObjects;

class Cube : public Utility {
public:
    Cube(float x, float y, float z, float width, float height, float depth,
         const std::vector<float>& color, unsigned int textureID);
    
    void updateVertices();
    
private:
    float width, height, depth;
    std::vector<float> color;
    unsigned int textureID;
};

class Square : public Utility {
public:
    Square(float x, float y, float width, float height, const std::vector<float>& color, unsigned int textureID = 0);
    void updateVertices() override;

private:
    float width;
    float height;
    std::vector<float> color;
    unsigned int textureID;
};

class Line : public Utility {
public:
    Line(float x, float y, float thickness, float length, const std::vector<float>& color);
    float thickness, length;
    std::vector<float> color;

protected:
    void updateVertices() override;
};

class Circle : public Utility {
public:
    Circle(float x, float y, float radius, const std::vector<float>& color);
    float radius;
    std::vector<float> color;

protected:
    void updateVertices() override;
};