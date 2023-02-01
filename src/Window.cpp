#include "Window.hpp"

Rect rect(300,260,200,200);
Circle circ(830,360,100,10000);

Window::Window(const std::string &name, uint16_t w , uint16_t h){
    Init(name , w ,h);
}

void Window::Init(const std::string &name,uint16_t  w,uint16_t h)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {

        window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

        if (!window)
        {
            std::cout << " window failed to init. Error: " << SDL_GetError()
                      << '\n';
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        isRunning = true;

    }


}

void Window::handleEvent()
{
    SDL_Event event;


    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        this->isRunning = false;
        break;

    default:
        break;
    }
}


void Window::draw(Shape &shape){
    shape.Draw(this->renderer); 
}

    

void Window::update()
{

}

void Window::render()
{


    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw(rect);
    draw(circ);

    SDL_RenderPresent(renderer);
}


Window::~Window()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}