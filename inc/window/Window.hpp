#pragma once


class SDL_Window;

class Window{

public:
    static Window &getInstance(){
        static Window instance_;
        return instance_; 
    };
public:
    inline static int initialize(int width, int height, const char *title) { return getInstance().initializeInternal(width,height,title); };
    inline static void terminate() { return getInstance().terminateInternal(); };
    inline static void swapBuffers() { return getInstance().swapBuffersInternal(); };
    inline static bool isShouldClose() { return getInstance().isShouldCloseInternal(); };
private:
    Window(){};
    Window(const Window&) = default;
    Window& operator=(Window&) = default;

private:
    int initializeInternal(int width, int height, const char *title);
    void terminateInternal();
    void swapBuffersInternal();
    bool isShouldCloseInternal();
private:
    SDL_Window *window_;
};