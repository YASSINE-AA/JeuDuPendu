#ifndef GUI_HPP
#define GUI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

class GUI
{
    public:
    void init()
    {
        // Initialize SDL and SDL audio
        if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) != 0)
        {
            throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
        }
    }

    void initAudio()
    {
        // Initialize SDL_mixer with MP3 support
        int flag = MIX_INIT_MP3;
        if (Mix_Init(flag) != flag)
        {
            throw std::runtime_error("SDL_mixer initialization failed: " + std::string(Mix_GetError()));
        }
    }

    void initRenderer()
    {

        int flags = IMG_INIT_JPG | IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if ((initted & flags) != flags)
        {
            throw std::runtime_error("IMG_Init Error: " + std::string(IMG_GetError()));
        }

        if (TTF_Init() < 0)
        {
            throw std::runtime_error("SDL_ttf initialization failed: " + std::string(TTF_GetError()));
        }
    }

    void destroy()
    {
        SDL_Quit();
    }
};

#endif