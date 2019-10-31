#pragma once

#include <vector>
#include "Shader.h"
#include "Mesh.h"

#include <assimp/scene.h>

class Model {
public:
    Model(const std::string &path);
    void Draw(Shader shader);
private:
    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTextures;
    std::string directory;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType textureType, const std::string &typeName);
};



