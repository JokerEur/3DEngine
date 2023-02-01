#pragma once

#include <SDL2/SDL.h>



class Shape{
public:
    Shape(){};
    ~Shape(){};
public:
    virtual void Draw(SDL_Renderer *renderer) = 0;
    virtual void Move() = 0;
    virtual void Rotate() = 0;
protected:
    struct vertices
    {
        int x,y; 
        int w,h;
        
    } vertices; 
    
    struct  color
    {
        uint8_t R,G,B;
        uint8_t alph;
        
        
    } color {0,0,0,0};
    
    
};

class Rect : public Shape{
public: 
    Rect() = default;
    Rect(int x , int y , int w , int h);
    ~Rect() = default;
public:
    void Draw(SDL_Renderer *renderer) override;
    void Move() override{};
    void Rotate() override{};
};

class Circle : public Shape{
private:
    int radius{};
    int steps{};
    double beta{};

public:
    Circle() = default;
    Circle(int x0, int y0, int r, int steps);
    ~Circle() = default; 

public:  
    void Draw(SDL_Renderer *renderer) override;
    void Move() override{};
    void Rotate() override{};
};