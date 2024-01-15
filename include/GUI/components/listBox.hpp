#ifndef LISTBOX_HPP
#define LISTBOX_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "renderer.hpp"
#include <iostream>
#include <vector>

class ListBox
{
public:
    std::vector<std::string> data;
    Renderer renderer;
    int margin = 10;
    int listSize;
    int listPos;
    int wordCount;
    TTF_Font *font;
    SDL_Rect dimensions;

    int elementSpacing;
    ListBox(Renderer renderer, TTF_Font *font, std::vector<std::string> data, SDL_Rect dimensions, int elementSpacing) : renderer(renderer), data(data), font(font), dimensions(dimensions), elementSpacing(elementSpacing)
    {
        listPos = dimensions.y + margin;
        wordCount = data.size();
        listSize = wordCount * elementSpacing;
    }
    void render();
    void addItem();
    void removeItem();
    void handleEvents(SDL_Event e);
};

#endif