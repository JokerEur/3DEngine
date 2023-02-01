#include "Window.hpp"

Window &window = Window::getInstance();

const uint32_t FPS = 60;
const uint32_t frameDelay = 1000 / FPS;

int main(int argc, char const *argv[])
{
    uint32_t frameStart;
    uint32_t frameTime;

    while (window.running())
    {

        frameStart = SDL_GetTicks();

        window.update();
        window.render();
        window.handleEvent();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        else
        {
        }
    }
    return 0;
     
}
