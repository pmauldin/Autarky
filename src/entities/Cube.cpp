#include "Cube.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

std::vector<Vertex> calculateVertices();

void calculateFace(std::vector<Vertex> &vertices, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);

Cube::Cube() : mesh(calculateVertices()) {}

void Cube::Draw(const Shader &shader) const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, transform.Position);
    model = glm::rotate(model, glm::radians(transform.Rotation.x), glm::vec3(1.0f, 0.3f, 0.5f));
    model = glm::scale(model, transform.Scale);
    shader.setMat4("model", model);

    mesh.Draw(shader);
}

std::vector<Vertex> calculateVertices() {
    std::vector<Vertex> vertices;

    float size = 0.5f;

    glm::vec3 BOTTOM_LEFT_FRONT = glm::vec3(-size, -size, size);
    glm::vec3 BOTTOM_LEFT_BACK = glm::vec3(-size, -size, -size);
    glm::vec3 BOTTOM_RIGHT_FRONT = glm::vec3(size, -size, size);
    glm::vec3 BOTTOM_RIGHT_BACK = glm::vec3(size, -size, -size);
    glm::vec3 TOP_LEFT_FRONT = glm::vec3(-size, size, size);
    glm::vec3 TOP_LEFT_BACK = glm::vec3(-size, size, -size);
    glm::vec3 TOP_RIGHT_FRONT = glm::vec3(size, size, size);
    glm::vec3 TOP_RIGHT_BACK = glm::vec3(size, size, -size);

    calculateFace(vertices, TOP_LEFT_BACK, TOP_LEFT_FRONT, TOP_RIGHT_BACK, TOP_RIGHT_FRONT);             // TOP
    calculateFace(vertices, BOTTOM_RIGHT_BACK, BOTTOM_RIGHT_FRONT, BOTTOM_LEFT_BACK, BOTTOM_LEFT_FRONT); // BOTTOM
    calculateFace(vertices, TOP_LEFT_BACK, BOTTOM_LEFT_BACK, TOP_LEFT_FRONT, BOTTOM_LEFT_FRONT);         // LEFT
    calculateFace(vertices, TOP_RIGHT_FRONT, BOTTOM_RIGHT_FRONT, TOP_RIGHT_BACK, BOTTOM_RIGHT_BACK);     // RIGHT
    calculateFace(vertices, TOP_LEFT_FRONT, BOTTOM_LEFT_FRONT, TOP_RIGHT_FRONT, BOTTOM_RIGHT_FRONT);     // FRONT
    calculateFace(vertices, TOP_RIGHT_BACK, BOTTOM_RIGHT_BACK, TOP_LEFT_BACK, BOTTOM_LEFT_BACK);         // BACK

    return vertices;
}

void calculateFace(std::vector<Vertex> &vertices, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) {
    vertices.emplace_back(p1);
    vertices.emplace_back(p2);
    vertices.emplace_back(p3);
    vertices.emplace_back(p3);
    vertices.emplace_back(p2);
    vertices.emplace_back(p4);
}
