#include "Window.hpp"
#include "Events.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>



int main(int argc, char const *argv[])
{
    Window::initialize(1280,720,"Window");
    Events::initialize();

    while(!Window::isShouldClose()){
        Window::swapBuffers();
    }

    Window::terminate();
    return 0;
}
