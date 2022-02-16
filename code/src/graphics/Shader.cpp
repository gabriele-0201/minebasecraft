#ifndef SHADER_CPP
#define SHADER_CPP

#include "Shader.h"

using std::string;

Shader::Shader(const string& _filePath) : filePath{_filePath}, rendererId{0}, defCostruct{false} {
    ShaderProgramSource source = parseShader(filePath);
    GLCall(rendererId = createShader(source.vertexSource, source.fragmentSource));
}

Shader::~Shader() {
    std::cout << "DIO MEO" <<std::endl;
    GLCall(glDeleteProgram(rendererId));
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id =  glCreateShader(type);
    //openGL want a char array, this method only return a pointer to the first character
    const char* src = source.c_str();

    //pay attenction to leght attribute, nullptr means that the stirngs for the array of 
    //strings terminate with null and have not a specified termination
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    //Error Handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE) {
        //now we have to get the error message

        int lenght;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
        //char* message = (char*)alloca(lenght * sizeof(char));
        char message[lenght];
        GLCall(glGetShaderInfoLog(id, lenght, &lenght, message));
        std::cout << "Failed to compile the " << (type == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader" <<std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }
    else
        std::cout << "compile seuccesfully " << (type == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader" <<std::endl;

    return id;

}

int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    //We have now to bind the shader and get the relative input

    unsigned int program = glCreateProgram();
    GLCall(unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader));
    GLCall(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader));

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    //with this we delete the code from the gpu after bind it
    //it usefull to have if for debugging
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;

}

ShaderProgramSource Shader::parseShader(const std::string& filePath) {

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream (filePath);

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)) {
        if(line.find("#shader") != std::string::npos) {

            if(line.find("vertex") != std::string::npos) 
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            
        } else {
                ss[(int)type] << (line) <<'\n';
            }
    }

    return {ss[0].str(), ss[1].str()};
}

void Shader::bind() const {
    GLCall(glUseProgram(rendererId));
}

void Shader::unbind() const {
    GLCall(glUseProgram(0));
}


void Shader::setUniform4f (const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}


void Shader::setUniform1f (const std::string& name, float value) {
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform1i (const std::string& name, int value) {
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform4Matrix(const std::string &name, glm::mat4 value) {
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)));
}

int Shader::getUniformLocation(const std::string& name) {

    if (locationChace.find(name) != locationChace.end()) 
        return locationChace[name];

    GLCall(int location = glGetUniformLocation(rendererId, name.c_str()));
    if(location == -1)
        std::cout << "Warnging: uniform name: " << name << "does not exists" << std::endl;
    
    locationChace[name] = location;

    return location;        
}

#endif