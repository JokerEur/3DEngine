#include "Events.hpp"
#include "Window.hpp"

#include <iostream> 

#include "../color.hpp"

bool *Events::keys;
uint *Events::frames;
uint Events::current = 0;
float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;
bool Events::cursorStart = false;
bool Events::cursorLocked= false;
SDL_Event Events::event;

#define _MOUSE_BUTTONS 1024 


void cursor_position_callback(double xpos, double ypos){
    if(Events::cursorStart){
        Events::deltaX += xpos - Events::x;
        Events::deltaY += ypos - Events::y;
    }else{
        Events::cursorStart = true;
    }
    Events::x = xpos;
    Events::y = ypos;
}

void mouse_button(int button ,  int action , int mode){
   if(action == SDL_KEYDOWN){
       Events::keys[_MOUSE_BUTTONS + button] = true;
       Events::frames[_MOUSE_BUTTONS + button] = Events::current;
   }else if(action == SDL_KEYUP){
       Events::keys[_MOUSE_BUTTONS + button] = false;
       Events::frames[_MOUSE_BUTTONS + button] = Events::current;
   }
}

void key_callback(int key , int action ){
   if(action == SDL_KEYDOWN){
       Events::keys[key] = true;
       Events::frames[key] = Events::current;
   }else if(action == SDL_KEYUP){
       Events::keys[key] = false;
       Events::frames[key] = Events::current;
   }
}


bool Events::pressed(ptrdiff_t keycode){
    if(keycode < 0 || keycode >= _MOUSE_BUTTONS){
        return false;
    }
    return keys[keycode];
}

bool Events::justPressed(ptrdiff_t keycode){
    if(keycode < 0 || keycode >= _MOUSE_BUTTONS){
        return false;
    }
    return keys[keycode] && frames[keycode] == current;
}


int Events::initialize(){

    keys =  new bool[1032];
    frames = new uint[1032]; 

    memset(keys,false , 1032*sizeof(bool));
    memset(frames, 0 , 1032*sizeof(uint));

    return 0; 
}


void Events::pullEvents(){
    
    current++;
    deltaX = 0.0f;
    deltaY = 0.0f;

    while(SDL_PollEvent(&Events::event)){
        if(Events::event.type == SDL_QUIT){
            std::cout << BOLDYELLOW << "WARNING::SDL: exit requeued!\n"<< RESET << '\n';
            Window::terminate();
        }

        if(Events::event.type == SDL_KEYUP){
            switch(Events::event.key.keysym.sym){
                case SDLK_ESCAPE:
                    std::cout << BOLDGREEN << "SDL_QUIT was requested\n" << RESET;
                    key_callback(SDLK_ESCAPE,SDL_KEYUP);
                    Window::terminate();
                    break;
            }
        }
        
    }
    
}