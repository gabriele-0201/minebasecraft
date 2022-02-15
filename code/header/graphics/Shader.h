#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

//#include "Renderer.h"
#include "GLC.h"

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {

    private:

        std::string filePath;
        unsigned int rendererId;
        int getUniformLocation(const std::string& name);

        // chaching for uniform
        std::unordered_map<std::string, int> locationChace;

        unsigned int compileShader(unsigned int type, const std::string& source);
        int createShader(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderProgramSource parseShader(const std::string& filePath);

    public:

        //Shader();
        Shader(const std::string& _filePath);
        ~Shader();

        void bind() const;
        void unbind() const;

        // Set uniforms
        void setUniform4f (const std::string& name, float v0, float v1, float v2, float v3);
        void setUniform1f (const std::string& name, float value);
        void setUniform1i (const std::string& name, int value);
        void setUniform4Matrix(const std::string &name, glm::mat4 value);

};

#endif