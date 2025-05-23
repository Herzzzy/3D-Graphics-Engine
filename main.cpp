#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "render.h"
#include "entity.h"
#include "camera.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "textureLoader.h"  


int screenWidth = 800;
int screenHeight = 600;
float xyRelation = static_cast<float>(screenWidth) / screenHeight;

float lastFrameTime = 0.0f;

float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), xyRelation);

void rebuildAllShapes();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void rebuildAllShapes() {
    for (auto object : gameObjects) {
        object->Rebuild();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
    xyRelation = static_cast<float>(screenWidth) / screenHeight;
    camera.aspectRatio = xyRelation;
    rebuildAllShapes();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

const int targetFPS = 60;
const std::chrono::duration<double> frameDuration(1.0 / targetFPS);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Graphics engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    const char* home = getenv("HOME");
    std::string full_path = std::string(home) + "/Documents/Graphics engine/textures/laminate_floor_02_diff_4k.jpg";

    unsigned int myTexture = loadTexture(full_path.c_str());

    glEnable(GL_DEPTH_TEST);

    std::vector<float> cubeColor = {0.0f, 1.0f, 0.0f};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            new Cube(-1.0f+i, -1.0f, 2.0f+j, 1.0f, 0.15f, 1.0f, 
                cubeColor, myTexture);
        }
    }

    while (!glfwWindowShouldClose(window)) {

        auto frameStart = std::chrono::high_resolution_clock::now();

        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }

        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        camera.ProcessKeyboardInput(window, deltaTime);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = camera.GetProjectionMatrix();

        for (auto object : gameObjects) {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 mvp = projection * view * model;
            object->Draw(mvp);
        }

        glfwSwapBuffers(window);

        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = frameEnd - frameStart;
        if (elapsed < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }

    glfwTerminate();
    return 0;
}