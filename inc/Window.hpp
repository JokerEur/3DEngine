#pragma once


class SDL_Window;

class Window{

public:
    static SDL_Window *window;

    static int initialize(int width, int height, const char *title);
    static void terminate();
    static void swapBuffers();
    static bool isShouldClose();

};