#include "listBox.hpp"

void ListBox::render()
{
    renderer.renderRect(dimensions);
    for (size_t i = 0; i < wordCount; ++i)
    {
        if (listPos + elementSpacing - dimensions.y > 0)
            renderer.renderFont(font, (std::to_string(i + 1) + " " + data[i]).c_str(), (SDL_Color){0, 0, 0}, 200, listPos + elementSpacing);
        elementSpacing += 40;
        if (listPos + elementSpacing - 100 > dimensions.h)
            break;
    }
    elementSpacing = 0;
}

void ListBox::handleEvents(SDL_Event e)
{
    if (e.type == SDL_MOUSEWHEEL)
    {
        int y = e.wheel.y;

        if (y == 1)
        {
            // UP
            if (listPos < 110)
            {
                listPos += 40;
            }
        }
        else
        {
            // DOWN
            if (dimensions.y - listPos < listSize - 12 * 40)
            {
                listPos -= 40;
            }
        }
    }
}
