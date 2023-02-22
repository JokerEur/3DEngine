#include "Events.hpp"
#include <SDL2/SDL.h>

bool *Events::_keys;
uint *Events::_frames;
uint Events::_current = 0;
float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;
bool Events::_cursor_start = false;
bool Events::_cursor_locked= false;

#define _MOUSE_BUTTONS 1024 

void cursor_position_callback(SDL_Window *window, double xpos, double ypos){
    if(Events::_cursor_start){
        Events::deltaX += xpos - Events::x;
        Events::deltaY += ypos - Events::y;
    }else{
        Events::_cursor_start = true;
    }
    Events::x = xpos;
    Events::y = ypos;
}

void mouse_button(SDL_Window *window, int button ,  int action , int mode){
   if(action == SDL_PRESSED){
       Events::_keys[_MOUSE_BUTTONS + button] = true;
       Events::_frames[_MOUSE_BUTTONS + button] = Events::_current;
   }else if(action == SDL_RELEASED){
       Events::_keys[_MOUSE_BUTTONS + button] = false;
       Events::_frames[_MOUSE_BUTTONS + button] = Events::_current;
   }
}

void key_callback(SDL_Window *window, int key , int scancode ,  int action , int mode){
   if(action == SDL_PRESSED){
       Events::_keys[key] = true;
       Events::_frames[key] = Events::_current;
   }else if(action == SDL_RELEASED){
       Events::_keys[key] = false;
       Events::_frames[key] = Events::_current;
   }
}


int Events::initialize(){

    SDL_Window *window = Window::window;
    _keys =  new bool[1032];
    _frames = new uint[1032]; 

    memset(_keys,false , 1032*sizeof(bool));
    memset(_frames, 0 , 1032*sizeof(uint));

    

    return 0; 
}

void Events::pullEvents(){
    _current++;
    deltaX = 0.0f;
    deltaY = 0.0f;
}