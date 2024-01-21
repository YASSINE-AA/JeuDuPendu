#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "customComponent.hpp"

class ListBox : public CustomComponent
{
public:
    ListBox(Renderer &renderer, States &states, TTF_Font *font, std::vector<std::string> &data, SDL_Rect &dimensions, int elementSpacing)
        : CustomComponent(renderer, states), data(data), font(font), dimensions(dimensions), elementSpacing(elementSpacing)
    {
        listPos = dimensions.y + margin;
        wordCount = data.size();
        listSize = wordCount * elementSpacing;
        originalSpacing = elementSpacing;
    }

    void render() override;
    void pushItem(std::string);
    int getLastHoveredItem();
    void removeItem(int idx);
    void listAllItems() {
        for(const std::string& word : data) {
            std::cout << word << std::endl;
        }
    }
    void setPosition(int x, int y) override
    {
        dimensions.x = x;
        dimensions.y = y;
    }
    void handleEvents(SDL_Event e) override;
    void updateParams();

private:
    std::vector<std::string> data;
    int originalSpacing;
    int listSize;
    int listPos;
    int wordCount;
    int lastHoveredItem;
    int margin = 10;
    TTF_Font *font;
    SDL_Rect dimensions;
    int elementSpacing;
};

#endif
