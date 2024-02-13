#include "window.hpp"

void Window::createWindow(int x, int y, int w, int h) {
    width = w;
    height = h;
    win = SDL_CreateWindow("Hangman", x, y, w, h, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
    }
}

void Window::deleteWindow() {
    if (win != nullptr) {
        SDL_DestroyWindow(win);
        win = nullptr;
    } else {
        std::cerr << "Window is already destroyed" << std::endl;
    }
}

std::tuple<int, int> Window::getWindowDimensions() {
    return {width, height};
}

SDL_Window* Window::getWindow() {
    return win;
}