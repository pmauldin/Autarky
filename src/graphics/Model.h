#pragma once

#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "../vendor/tiny_obj_loader.h"

class Model {
public:
    explicit Model(const std::string &path);
    void Draw(Shader shader);
private:
    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTextures;
    std::string directory;

    void loadModel(const std::string &path);
    Texture loadDiffuseTexture(tinyobj::material_t &mat);
};



