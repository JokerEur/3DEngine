#pragma once

#include <string>

class Texture{

public:
    Texture(unsigned int id , int width, int height);
    ~Texture(); 
public:
    void bind(); 
public:
    unsigned int id;
    int width;
    int height; 

};

extern Texture* load_texture(std::string filename);

