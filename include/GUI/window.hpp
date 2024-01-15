#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Window
{
public:
    // Window and Renderer Functions

    void createWindow(int x, int y, int w, int h)
    {
        // Create SDL window
        win = SDL_CreateWindow("Hangman", x, y, w, h, SDL_WINDOW_SHOWN);
        if (win == nullptr)
        {
            throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        }
    }

    void deleteWindow()
    {
        if (win != nullptr)
        {
            SDL_DestroyWindow(win);
            win = nullptr;
        }
        else
        {
            std::cerr << "Window is already destroyed" << std::endl;
        }
    }

    SDL_Window *getWindow(){return win;}

private:
    SDL_Window *win;
};

#endif
