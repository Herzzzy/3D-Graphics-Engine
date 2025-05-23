#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
    public:
        float aspectRatio;
        Camera(glm::vec3 position, float aspectRatio);
    
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        void ProcessKeyboardInput(GLFWwindow* window, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset);
        void UpdateCameraVectors();
    
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
    
    private:
        float yaw = -90.0f;
        float pitch = 0.0f;
        float fov;
    };