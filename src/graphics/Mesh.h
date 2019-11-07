#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

struct Vertex {
    glm::vec3 Position;
};

class Mesh {
public:
    unsigned int VAO = 0;

    explicit Mesh(std::vector<Vertex> vertices);

    void Draw(const Shader &shader) const;
private:
    std::vector<Vertex> vertices;
};
