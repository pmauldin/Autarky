#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

std::string getShaderSource(const std::string &filePath);
unsigned int compileShader(const char* source, bool isVertex);

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string vertexShaderSource = getShaderSource(vertexPath);
    std::string fragmentShaderSource = getShaderSource(fragmentPath);

    unsigned int vertexShader = compileShader(vertexShaderSource.c_str(), true);
    unsigned int fragmentShader = compileShader(fragmentShaderSource.c_str(), false);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    int success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        exit(-1);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

// Helper Functions //
std::string getShaderSource(const std::string &filePath) {
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string shaderSource;
    try {
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        shaderSource = shaderStream.str();
    } catch (std::ifstream::failure &ex) {
        std::cout << "Unable to open shader file at " << filePath << std::endl;
        exit(-1);
    }

    return shaderSource;
}

unsigned int compileShader(const char* source, bool isVertex) {
    unsigned int shader;

    if (isVertex) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::" << (isVertex ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog
                  << std::endl;
        exit(-1);
    }

    return shader;
}