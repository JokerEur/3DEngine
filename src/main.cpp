#include "Window.hpp"
#include "Events.hpp"
#include "graphics/Shader.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>



void kill(){
    SDL_Quit();
}

int main(int argc, char const *argv[])
{
    Window::initialize(1280,720,"Window");
    Events::initialize();

    Shader *shader = loadShader("res/main.glslv", "res/main.glslf");



    while(!Window::isShouldClose()){
        Events::pullEvents();
        Window::swapBuffers();
    }

    Window::terminate();
    return 0;
}
