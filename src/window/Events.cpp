#include "Events.hpp"
#include "Window.hpp"
#include "Camera.hpp"

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
std::unique_ptr<SDL_Event> Events::event = std::unique_ptr<SDL_Event>(new SDL_Event);

Camera* camera = new Camera(glm::vec3(0,0,1) , glm::radians(70.0f)); //! fix this Camera variable

#define _MOUSE_BUTTONS 1024 

void cursor_position_callback(int key, int action){
    if(Events::cursorStart){
        Events::deltaX += Events::event->motion.x - Events::x;
        Events::deltaY += Events::event->motion.y - Events::y;
    }else{
        Events::cursorStart = true;
    }
    Events::x = Events::event->motion.x;
    Events::y = Events::event->motion.y;
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

bool Events::pressedInternal(ptrdiff_t keycode){
    if(keycode < 0 || keycode >= _MOUSE_BUTTONS){
        return false;
    }
    return keys[keycode];
}

bool Events::justPressedInternal(ptrdiff_t keycode){
    if(keycode < 0 || keycode >= _MOUSE_BUTTONS){
        return false;
    }
    return keys[keycode] && frames[keycode] == current;
}

void Events::toogleCursorInternal(){
    cursorLocked = !cursorLocked;
    Window::setCursorMode(cursorLocked ? SDL_TRUE : SDL_FALSE);
}


int Events::initializeInternal(){

    keys =  new bool[1032];
    frames = new uint[1032]; 

    memset(keys,false , 1032*sizeof(bool));
    memset(frames, 0 , 1032*sizeof(uint));

    
   Events::registerCallback(SDL_KEYDOWN, key_callback);
   Events::registerCallback(SDL_KEYUP, key_callback);
   Events::registerCallback(SDL_MOUSEMOTION , cursor_position_callback);


    return 0; 
}


void Events::registerCallbackInternal(uint32_t type, eventCallback callback){
    callbacks_[type] = callback;
}

void Events::unregisterCallbackInternal(uint32_t type){
    callbacks_.erase(type);
}


void Events::pullEventsInternal(){
    
    current++;
    deltaX = 0.0f;
    deltaY = 0.0f;


    while(SDL_PollEvent(Events::event.get())){

        auto it = callbacks_.find(Events::event->type);

        if(Events::event->type == SDL_QUIT){
            std::cout << BOLDYELLOW << "WARNING::SDL: exit requeued!\n"<< RESET << '\n';
            SDL_Quit();
        }

        if(it != callbacks_.end()){
            it->second(Events::event->key.keysym.sym,Events::event->type);
        }
    }
    
}