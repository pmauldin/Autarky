#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    void use();

    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 &value) const;
private:
    unsigned int ID;
};



