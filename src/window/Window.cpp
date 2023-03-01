#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "Window.hpp"
#include "Events.hpp"
#include "../color.hpp"


int Window::initializeInternal(int width , int height, const char *title){
    SDL_Init(SDL_INIT_EVERYTHING);
    
    window_ = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height, SDL_WINDOW_OPENGL);
    if(window_ == nullptr){
        std::cerr << RED << "Failed to create SLD Widnow" << RESET << std::endl;
        SDL_Quit(); 
        return -1;
    }

    SDL_GL_CreateContext(window_);

    if(glewInit() != GLEW_OK){
        std::cerr << BOLDRED << "Failed to initialize GLEW with errro: " << glewGetErrorString(glewInit()) << RESET << std::endl; 
        return -1;
    }  
    glViewport(0,0,width,height);
    return 0;
}

void Window::terminateInternal(){
    SDL_DestroyWindow(window_); 
    SDL_Quit();
}

void Window::swapBuffersInternal(){
    SDL_GL_SwapWindow(window_);
}

bool Window::isShouldCloseInternal(){
    return (Events::event.type == SDL_QUIT);
}