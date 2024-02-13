#include "gui.hpp"

void GUI::init() {
    // Initialize SDL and SDL audio
    if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) != 0) {
        throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
    }
}

void GUI::initAudio() {
    // Initialize SDL_mixer with MP3 support
    int flag = MIX_INIT_MP3;
    if (Mix_Init(flag) != flag) {
        throw std::runtime_error("SDL_mixer initialization failed: " + std::string(Mix_GetError()));
    }
}

void GUI::initRenderer() {
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags) {
        throw std::runtime_error("IMG_Init Error: " + std::string(IMG_GetError()));
    }

    if (TTF_Init() < 0) {
        throw std::runtime_error("SDL_ttf initialization failed: " + std::string(TTF_GetError()));
    }
}

void GUI::destroy() {
    SDL_Quit();
}
