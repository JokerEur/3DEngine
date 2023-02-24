#pragma once 

#include <SDL2/SDL.h>

typedef unsigned int uint;

class Events{

public:
    static bool *keys;
    static uint *frames;
    static uint current;
    static float deltaX;
    static float deltaY;
    static float x; 
    static float y;
    static bool cursorLocked;
    static bool cursorStart;
    static SDL_Event event;

    static int initialize();
    static void pullEvents();

    static bool pressed(ptrdiff_t keycode);
    static bool justPressed(ptrdiff_t keycode);

};