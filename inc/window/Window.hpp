#pragma once

#include<memory>
#include <SDL2/SDL.h>

struct SDLWindowDeleter {
    inline void operator()(SDL_Window* window) {
        SDL_DestroyWindow(window);
    }
};

class Window{
public:
    static Window &getInstance(){
        static Window instance_;
        return instance_; 
    };
public:
    inline static int initialize(int width, int height, const char *title) { return getInstance().initializeInternal(width,height,title); };
    inline static bool isShouldClose() { return getInstance().isShouldCloseInternal(); };
    inline static void terminate() { getInstance().terminateInternal(); };
    inline static void swapBuffers() { getInstance().swapBuffersInternal(); };
    inline static void setCursorMode(SDL_bool mode) { getInstance().setCursorModeInternal(mode); };
    
private:
    Window(){};
    Window(const Window&) = delete;
    Window& operator=(Window&) = delete;

private:
    int initializeInternal(int width, int height, const char *title);
    bool isShouldCloseInternal();
    void terminateInternal();
    void swapBuffersInternal();
    void setCursorModeInternal(SDL_bool mode);
private:
    std::unique_ptr<SDL_Window, SDLWindowDeleter> window_;
    
    
};