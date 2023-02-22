#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "Window.hpp"
#include "color.hpp"

SDL_Window *Window::window;



int Window::initialize(int width , int height, const char *title){
    SDL_Init(SDL_INIT_EVERYTHING);
    
    window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height, SDL_WINDOW_OPENGL);
    if(window == nullptr){
        std::cerr << RED << "Failed to create SLD Widnow" << RESET << std::endl;
        SDL_Quit(); 
        return -1;
    }

    SDL_GL_CreateContext(window);

    if(glewInit() != GLEW_OK){
        std::cerr << BOLDRED << "Failed to initialize GLEW with errro: " << glewGetErrorString(glewInit()) << RESET << std::endl; 
        return -1;
    }  
    glViewport(0,0,width,height);
    return 0;
}

void Window::terminate(){
    SDL_DestroyWindow(window); 
    SDL_Quit();
}

void Window::swapBuffers(){
    SDL_GL_SwapWindow(window);
}

bool Window::isShouldClose(){
    SDL_Event event;
    SDL_PollEvent(&event);
    return (event.type == SDL_QUIT);
}