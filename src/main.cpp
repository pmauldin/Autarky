#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/Shader.h"
#include "graphics/Model.h"

void initOpenGL();

void processInput();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* window;
int screenWidth = 1280, screenHeight = 720;

// Camera
float speed = 2.6f;
float camX = 0.0f, camY = 0.0f, camZ = 3.0f;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
    initOpenGL();

    Shader shader("./resources/shaders/default.vert", "./resources/shaders/default.frag");
    shader.use();

    glm::mat4 model(1.0f);
    glm::mat4 projection = glm::perspective(45.0f, (float) screenWidth / (float) screenHeight, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    Model nanosuit("./resources/models/nanosuit/nanosuit.obj");

    while (!glfwWindowShouldClose(window)) {
        // Timestep
        auto currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(-camX, -camY, -camZ));
        shader.setMat4("view", view);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down
        shader.setMat4("model", model);

        nanosuit.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_W)) {
        camZ -= speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        camZ += speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        camX -= speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        camX += speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        camY += speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        camY -= speed * deltaTime;
    }

}

void initOpenGL() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, "Autarky", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glm::vec2 windowCenter(mode->width / 2, mode->height / 2);
    glfwSetWindowPos(window, (int) windowCenter.x - (screenWidth / 2), (int) windowCenter.y - (screenHeight / 2));

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Disable V-Sync
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
}

void framebuffer_size_callback(GLFWwindow* w, int width, int height) {
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
}
