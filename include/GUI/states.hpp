// states.hpp

#ifndef STATES_HPP
#define STATES_HPP

#include <SDL2/SDL.h>

class States {
public:
    char convertSDLKeyToChar(SDL_Keycode key);
    void getMousePosition(int* x, int* y);
    bool isBtnArea(int mouseX, int mouseY, SDL_Rect rect);
};

#endif
