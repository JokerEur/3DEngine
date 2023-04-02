#pragma once

#include <string>
#include <glm/glm.hpp>


class Shader{
    public:
        Shader(unsigned int id);
        ~Shader();
    public:
        void use();
        void uniformMatrix(std::string name, glm::mat4 matrix);
    public:
        unsigned int id;
};

//TODO fix potential memory leaks and problem with relevant paths
extern Shader *loadShader(std::string vertexFile , std::string fragmentFile);