#pragma once

#include <glm/glm.hpp>
#include "../graphics/Shader.h"

struct Transform {
    glm::vec3 Position;
    glm::vec3 Scale;
    glm::vec3 Rotation;
};

class Entity {
public:
    Transform transform = { {}, { 1.0f, 1.0f, 1.0f }, {} };

    virtual void Draw(const Shader &shader) const = 0;
};
