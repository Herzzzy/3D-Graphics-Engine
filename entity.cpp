#include "entity.h"
#include <cmath>

#define PI 3.14159265358979323846f

std::vector<Utility*> gameObjects;
extern float xyRelation;

Utility::Utility(float x, float y, float z) : x(x), y(y), z(z) {
    gameObjects.push_back(this);
}

void Utility::Move(float dx, float dy, float dz) {
    x += dx;
    y += dy;
    z += dz;
    updateVertices();
}

void Utility::Draw(const glm::mat4& vp) {
    for (auto& face : faces) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
        glm::mat4 mvp = vp * model;
        face->Draw(mvp);
    }
}

Cube::Cube(float x, float y, float z, float width, float height, float depth,
    const std::vector<float>& color, unsigned int textureID)
: Utility(x, y, z), width(width), height(height), depth(depth), color(color), textureID(textureID) {
updateVertices();
}

void Cube::updateVertices() {
    faces.clear();

    float w = width / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;

    std::vector<float> vertices = {
        -w, -h, -d, 0.0f, 0.0f,
         w, -h, -d, 1.0f, 0.0f,
         w,  h, -d, 1.0f, 1.0f,
        -w,  h, -d, 0.0f, 1.0f,

        -w, -h,  d, 0.0f, 0.0f,
         w, -h,  d, 1.0f, 0.0f,
         w,  h,  d, 1.0f, 1.0f,
        -w,  h,  d, 0.0f, 1.0f,

        -w, -h, -d, 0.0f, 0.0f,
        -w,  h, -d, 1.0f, 0.0f,
        -w,  h,  d, 1.0f, 1.0f,
        -w, -h,  d, 0.0f, 1.0f,

         w, -h, -d, 0.0f, 0.0f,
         w,  h, -d, 1.0f, 0.0f,
         w,  h,  d, 1.0f, 1.0f,
         w, -h,  d, 0.0f, 1.0f,

        -w,  h, -d, 0.0f, 0.0f,
         w,  h, -d, 1.0f, 0.0f,
         w,  h,  d, 1.0f, 1.0f,
        -w,  h,  d, 0.0f, 1.0f,

        -w, -h, -d, 0.0f, 0.0f,
         w, -h, -d, 1.0f, 0.0f,
         w, -h,  d, 1.0f, 1.0f,
        -w, -h,  d, 0.0f, 1.0f,
    };

    std::vector<unsigned int> indices;
    for (int i = 0; i < 6; ++i) {
        unsigned int base = i * 4;
        indices.push_back(base + 0);
        indices.push_back(base + 1);
        indices.push_back(base + 2);
        indices.push_back(base + 2);
        indices.push_back(base + 3);
        indices.push_back(base + 0);
    }

    faces.push_back(std::make_shared<Render>(vertices, indices, color, textureID));
}

Square::Square(float x, float y, float width, float height, const std::vector<float>& color, unsigned int textureID)
    : Utility(x, y, 0.0f), width(width), height(height), color(color), textureID(textureID) {
    updateVertices();
}

void Square::updateVertices() {
    faces.clear();

    float w = width / 2.0f;
    float h = height / 2.0f;

    std::vector<float> vertices;
    if (textureID != 0) {
        vertices = {
            -w, -h, 0.0f, 0.0f, 0.0f,
             w, -h, 0.0f, 1.0f, 0.0f,
             w,  h, 0.0f, 1.0f, 1.0f,
            -w,  h, 0.0f, 0.0f, 1.0f
        };
    } else {
        vertices = {
            -w, -h, 0.0f,
             w, -h, 0.0f,
             w,  h, 0.0f,
            -w,  h, 0.0f
        };
    }

    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };
    faces.push_back(std::make_shared<Render>(vertices, indices, color, textureID));
}

Line::Line(float x, float y, float thickness, float length, const std::vector<float>& color)
    : Utility(x, y, 0.0f), thickness(thickness), length(length), color(color) {
    updateVertices();
}

void Line::updateVertices() {
    faces.clear();

    float l = length / 2.0f;
    float t = thickness / 2.0f;

    std::vector<float> vertices = {
        -l, -t, 0.0f,
         l, -t, 0.0f,
         l,  t, 0.0f,
        -l,  t, 0.0f
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };
    faces.push_back(std::make_shared<Render>(vertices, indices, color));
}

Circle::Circle(float x, float y, float radius, const std::vector<float>& color)
    : Utility(x, y, 0.0f), radius(radius), color(color) {
    updateVertices();
}

void Circle::updateVertices() {
    faces.clear();
    const int segments = 64;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        vertices.push_back(std::cos(angle) * radius);
        vertices.push_back(std::sin(angle) * radius);
        vertices.push_back(0.0f);
        if (i > 0) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }

    faces.push_back(std::make_shared<Render>(vertices, indices, color));
}