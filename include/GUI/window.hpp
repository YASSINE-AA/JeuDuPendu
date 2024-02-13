// window.hpp

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <stdexcept>
#include <tuple>
#include <iostream>
#include <SDL2/SDL.h>

class Window {
public:
    void createWindow(int x, int y, int w, int h);
    void deleteWindow();
    std::tuple<int, int> getWindowDimensions();
    SDL_Window* getWindow();

private:
    SDL_Window* win;
    int width;
    int height;
};

#endif
