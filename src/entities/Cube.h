#pragma once

#include "../graphics/Mesh.h"

class Cube {
public:
    explicit Cube();

    void Draw(const Shader &shader) const;
private:
    Mesh mesh;
};
