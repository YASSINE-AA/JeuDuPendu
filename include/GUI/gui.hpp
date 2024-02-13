// gui.hpp

#ifndef GUI_HPP
#define GUI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <stdexcept>

class GUI {
public:
    void init();
    void initAudio();
    void initRenderer();
    void destroy();
};

#endif
