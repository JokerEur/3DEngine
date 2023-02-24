#pragma once

#include <string>

class Shader{
    public:
        Shader(unsigned int id);
        ~Shader();
    public:
        void use();
    public:
        unsigned int id;
};

extern Shader *loadShader(std::string vertexFile , std::string fragmentFile);