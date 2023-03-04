#pragma once 

#include <SDL2/SDL.h>
#include <functional>

typedef unsigned int uint;

class Events{
public:
static Events &getInstance(){
    static Events instance_;
    return instance_;
};
public:
    inline static int initialize() { return getInstance().initializeInternal(); };
    inline static void pullEvents() { return getInstance().pullEventsInternal(); };
    inline static bool pressed(ptrdiff_t keycode) { return getInstance().pressedInternal(keycode); };
    inline static bool justPressed(ptrdiff_t keycode) {return getInstance().justPressedInternal(keycode); };

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
    std::function<void(uint32_t type)> eventCallback;

    

private: 
    Events(){};
    Events(const Events&) = default;
    Events& operator= (Events&) = default;
private: 
    

private:
    int initializeInternal();
    void pullEventsInternal();
    bool pressedInternal(ptrdiff_t keycode);
    bool justPressedInternal(ptrdiff_t keycode);
    void registerCallback(SDL_Event* e);
    void unregisterCallback(uint32_t type);
};