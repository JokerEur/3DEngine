#pragma once 

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "Shape.hpp"


class Window final{

private:
    std::string name{};
    uint16_t w ,h;
    SDL_Window * window{nullptr};

    bool isRunning{};

public:
    Window(const Window &) = delete;
    Window &operator =(const Window &) = delete;

private:
    Window(const std::string &name, uint16_t w , uint16_t h); 

private:
    ~Window();

public:
    static Window &getInstance(){
        static Window instance("Window", 1280, 720);
        return instance;
    }; 

public: 
    SDL_Renderer *renderer{nullptr};

    void Init(const std::string &name , uint16_t w , uint16_t h);
    void handleEvent();
    void render();
    void update();
    void draw(Shape &shape);
    inline bool running() {return this->isRunning;};
    inline SDL_Window *getWindow() { return this->window;};



};