#include "Shader.hpp"

#include<exception>
#include<fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "../color.hpp"


Shader::Shader(unsigned int id) : id(id) {}


Shader::~Shader(){
    glDeleteProgram(id);
}

void Shader::use(){
    glUseProgram(id);
}


Shader *loadShader(std::string vertexFile , std::string fragmentFile){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);

    try{
        vShaderFile.open(vertexFile);
        fShaderFile.open(fragmentFile);
        std::stringstream vShaderStream , fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure &e){
        std::cerr<< BOLDRED << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << RESET << '\n';
    }

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    GLuint vertex , fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(vertex , 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << BOLDRED << "SHADER::VERTEX: compilation failed" << RESET << '\n';
        std::cerr << infoLog << '\n';
        return nullptr;
    }
    
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER); 
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << BOLDRED << "SHADER::FRAGMENT: compilation failed" << RESET << '\n';
        std::cerr << infoLog << '\n';
        return nullptr;
    }
    
    GLuint id = glCreateProgram();
    glAttachShader(id ,vertex); 
    glAttachShader(id , fragment);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cerr << BOLDRED << "SHADER::PROGRAM: linking failed" << RESET << '\n';
        std::cerr << infoLog << '\n';

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(id);

        return nullptr;
    }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
 
        return new Shader(id);

}


