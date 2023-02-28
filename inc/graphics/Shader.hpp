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

//TODO fix potential memory leaks and problem with relevant paths
extern Shader *loadShader(std::string vertexFile , std::string fragmentFile);