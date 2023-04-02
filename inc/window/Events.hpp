#pragma once 

#include <SDL2/SDL.h>
#include <functional>
#include <memory>
#include <map>

typedef unsigned int uint;

class Events{
public:
static Events &getInstance(){
    static Events instance_;
    return instance_;
};
public:
    inline static int initialize() { return getInstance().initializeInternal(); };
    inline static void pullEvents() { getInstance().pullEventsInternal(); };
    inline static bool pressed(ptrdiff_t keycode) { return getInstance().pressedInternal(keycode); };
    inline static bool justPressed(ptrdiff_t keycode) {return getInstance().justPressedInternal(keycode); };
    inline static void toogleCursor() { getInstance().toogleCursorInternal(); };

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
    
    static std::unique_ptr<SDL_Event> event;
    typedef std::function<void(uint32_t keycode, uint32_t action)> eventCallback;

private: 
    Events(){};
    Events(const Events&) = default;
    Events& operator= (Events&) = default;
private: 
    std::map<uint32_t, eventCallback> callbacks_;
private:
    int initializeInternal();
    void pullEventsInternal();
    bool pressedInternal(ptrdiff_t keycode);
    bool justPressedInternal(ptrdiff_t keycode);
    void registerCallbackInternal(uint32_t type , eventCallback callback);
    void unregisterCallbackInternal(uint32_t type);
    void toogleCursorInternal();
private:
    static inline void registerCallback(uint32_t type , eventCallback callback) {return getInstance().registerCallbackInternal(type,callback);} ;
    static inline void unregisterCallback(uint32_t type) { return getInstance().unregisterCallbackInternal(type); };
};