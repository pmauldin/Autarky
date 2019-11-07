#include "Mesh.h"

#include <utility>
#include <glad/glad.h>

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
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
}
