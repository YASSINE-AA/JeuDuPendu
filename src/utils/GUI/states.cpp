#include "states.hpp"

char States::convertSDLKeyToChar(SDL_Keycode key) {
    // Convert SDL key code to char
    if ((key >= SDLK_a && key <= SDLK_z) || (key >= SDLK_0 && key <= SDLK_9)) {
        return static_cast<char>(key);
    }
    return '\0';
}

void States::getMousePosition(int* x, int* y) {
    // Get current mouse position
    SDL_GetMouseState(x, y);
}

bool States::isBtnArea(int mouseX, int mouseY, SDL_Rect rect) {
    // Check if mouse is within a specified area
    if ((mouseX > rect.x && mouseX < rect.x + rect.w) && (mouseY > rect.y && mouseY < rect.y + rect.h)) {
        return true;
    }
    return false;
}
