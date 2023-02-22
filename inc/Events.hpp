#pragma once 

#include "Window.hpp"

typedef unsigned int uint;

class Events{

public:
    static bool *_keys;
    static uint *_frames;
    static uint _current;
    static float deltaX;
    static float deltaY;
    static float x; 
    static float y;
    static bool _cursor_locked;
    static bool _cursor_start;

    static int initialize();
    static void pullEvents();

};