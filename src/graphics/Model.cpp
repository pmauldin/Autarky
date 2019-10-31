#include "Model.h"
#include "../vendor/stb_image.h"

#include <iostream>
#include <glad/glad.h>
#include <cstring>

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma = false);

Model::Model(const std::string &path) {
    loadModel(path);
}

void Model::Draw(Shader shader) {
    for (auto &mesh : meshes) {
        mesh.Draw(shader);
    }
}

void Model::loadModel(const std::string &path) {
    directory = path.substr(0, path.find_last_of('/'));

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    auto success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), directory.c_str(), true);

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!success) {
        std::cerr << success << std::endl;
        exit(1);
    }

    // NOTE!
    // In order to use an element array buffer
    // I would have to manually find duplicate triplets (combination of <idx.vertex_index, idx.normal_index, idx.texture_index>)
    // And convert those to a set of vertices, and then construct the indices buffer.

    // Loop over meshes
    for (unsigned int s = 0; s < shapes.size(); s++) {
        unsigned int indexOffset = 0;
        auto mesh = shapes[s].mesh;

        std::vector<Vertex> vertices;
        std::vector<Texture> textures;

        // Loop over faces in mesh
        for (unsigned int f = 0; f < mesh.num_face_vertices.size(); f++) {
            int fv = mesh.num_face_vertices[f];

            // Loop over vertices in face
            for (unsigned int v = 0; v < fv; v++) {
                Vertex vertex{};
                glm::vec3 vector;

                tinyobj::index_t idx = mesh.indices[indexOffset + v];

                vector.x = attrib.vertices[3 * idx.vertex_index + 0];
                vector.y = attrib.vertices[3 * idx.vertex_index + 1];
                vector.z = attrib.vertices[3 * idx.vertex_index + 2];
                vertex.Position = vector;

                vector.x = attrib.normals[3 * idx.normal_index + 0];
                vector.y = attrib.normals[3 * idx.normal_index + 1];
                vector.z = attrib.normals[3 * idx.normal_index + 2];
                vertex.Normal = vector;

                glm::vec2 vec;
                if (idx.texcoord_index != -1) {
                    vec.x = attrib.texcoords[2 * idx.texcoord_index + 0];
                    vec.y = attrib.texcoords[2 * idx.texcoord_index + 1];
                    vertex.TexCoords = vec;
                } else {
                    vertex.TexCoords = glm::vec2(0.0f);
                }

                vertices.push_back(vertex);
            }
            indexOffset += fv;
        }

        if (!mesh.material_ids.empty()) {
            unsigned int materialIndex = mesh.material_ids.front();
            if (materialIndex >= 0) {
                tinyobj::material_t material = materials[materialIndex];
                textures.push_back(loadDiffuseTexture(material));
            }
        }

        meshes.emplace_back(vertices, textures);
    }
}

Texture Model::loadDiffuseTexture(tinyobj::material_t &mat) {
    std::string str = mat.diffuse_texname;

    for (auto &loadedTexture : loadedTextures) {
        if (std::strcmp(loadedTexture.path.data(), str.c_str()) == 0) {
            return loadedTexture;
        }
    }

    Texture texture;
    texture.id = TextureFromFile(str.c_str(), directory);
    texture.type = "texture_diffuse";
    texture.path = str;
    loadedTextures.push_back(texture);

    return texture;
}

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma) {
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        else {
            std::cerr << "Invalid nrComponents " << nrComponents << " for file " << filename;
            exit(-1);
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
