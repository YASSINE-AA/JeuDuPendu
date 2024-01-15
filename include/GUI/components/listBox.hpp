#ifndef LISTBOX_HPP
#define LISTBOX_HPP
#include "renderer.hpp"
#include "states.hpp"
class ListBox
{
public:
    std::vector<std::string> data;
    ListBox(Renderer renderer, States states, TTF_Font *font, std::vector<std::string> data, SDL_Rect dimensions, int elementSpacing) : renderer(renderer), data(data), font(font), dimensions(dimensions), elementSpacing(elementSpacing)
    {
        listPos = dimensions.y + margin;
        wordCount = data.size();
        listSize = wordCount * elementSpacing;
        originalSpacing = elementSpacing;
    }
    void render();
    void pushItem(std::string);
    int getLastHoveredItem();
    void removeItem(int idx);
    void handleEvents(SDL_Event e);

private:
    int originalSpacing;
    int listSize;
    int listPos;
    int wordCount;
    int lastHoveredItem;
    Renderer renderer;
    States states;
    int margin = 10;
    TTF_Font *font;
    SDL_Rect dimensions;
    int elementSpacing;
    void updateParams()
    {
        wordCount = data.size();
        listSize = wordCount * originalSpacing;
    }
};

#endif