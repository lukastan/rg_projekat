#ifndef PROJECT_BASE_SHADER_H
#define PROJECT_BASE_SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

std::string readFileContents(std::string path) {
    std::ifstream in(path);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

class Shader {
    unsigned int id;
    public:
        Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
            int success = 0;
            char infoLog[512];

            std::string vsString = readFileContents(vertexShaderPath);
            const char *vertexShaderSource = vsString.c_str();

            int vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
                std::cerr << "ERROR: SHADER VERTEX COMPILATION FAILED\n" << infoLog << "\n";
            }

            std::string fsString = readFileContents(fragmentShaderPath);
            const char *fragmentShaderSource = fsString.c_str();

            int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
                std::cerr << "ERROR: SHADER FRAGMENT COMPILATION FAILED\n" << infoLog << "\n";
            }

            int shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
                std::cerr << "ERROR: SHADER LINKING COMPILATION FAILED\n" << infoLog << "\n";
            }

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            id = shaderProgram;
        }

        void use() {
            glUseProgram(id);
        }

        void setUniform1i(std::string name, int i) {
            int uniformId = glGetUniformLocation(id, name.c_str());
            glUniform1i(uniformId, i);
        }

        void setUniform4f(std::string name, float x, float y, float z, float w) {
            int uniformId = glGetUniformLocation(id, name.c_str());
            glUniform4f(uniformId, x, y, z, w);
        }

        void setMat4(const std::string &name, const glm::mat4 &mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void deleteProgram() {
            glDeleteProgram(id);
        }
};

#endif