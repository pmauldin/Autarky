#pragma once

#include "../graphics/Mesh.h"
#include "Entity.h"

class Cube : public Entity {
public:
    explicit Cube();

    void Draw(const Shader &shader) const override;
private:
    Mesh mesh;
};
