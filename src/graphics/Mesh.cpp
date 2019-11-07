#include "Mesh.h"

#include <utility>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(std::vector<Vertex> vertices) : vertices(std::move(vertices)) {
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float vertexSize = sizeof(Vertex);
    float bufferSize = this->vertices.size() * vertexSize;

    glBufferData(GL_ARRAY_BUFFER, bufferSize, &this->vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Draw(const Shader &shader) const {
    glBindVertexArray(VAO);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.5f, -0.2f, -2.5f));
    model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1.0f, 0.3f, 0.5f));
    shader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
