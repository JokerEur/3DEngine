#include "Shape.hpp"


Rect::Rect(int x, int y , int w, int h){
    this->vertices.x = x;
    this->vertices.y = y;
    this->vertices.w = w;
    this->vertices.h = h;
}

void Rect::Draw(SDL_Renderer *renderer){

    this->color = {255,255,255,255};

    SDL_Rect rect;
    rect.x = this->vertices.x;
    rect.y = this->vertices.y;
    rect.h = this->vertices.h;
    rect.w = this->vertices.w;

    SDL_SetRenderDrawColor(renderer, this->color.R, this->color.G, this->color.B, this->color.alph);
    SDL_RenderDrawRect(renderer, &rect);

}


Circle::Circle(int x0 , int y0, int r, int steps){
    this->steps = steps;
    this->beta = M_PI * 2 / steps;

    this->radius = r;
    this->vertices.y = y0;
    this->vertices.x = x0;
}


void Circle::Draw(SDL_Renderer *renderer){

    this->color = {0,255,0,255};

    SDL_SetRenderDrawColor(renderer, this->color.R, this->color.G, this->color.B, this->color.alph);

    for(ptrdiff_t i{}; i < steps; ++i){

        float newX = radius * SDL_sin(beta*i) + vertices.x;
        float newY = -radius * SDL_cos(beta*i) + vertices.y;

        SDL_RenderDrawPoint(renderer,newX, newY);

    }
}




