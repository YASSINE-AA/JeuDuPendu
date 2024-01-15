#include "listBox.hpp"
void ListBox::render()
{
    SDL_Color normalColor = {0, 0, 0};
    SDL_Color color = normalColor;
    SDL_Color hoverColor = {255, 0, 0};

    int x, y;
    states.getMousePosition(&x, &y);
    renderer.renderRect(dimensions);
    for (size_t i = 0; i < wordCount; ++i)
    {
        color = normalColor;
        if (listPos + elementSpacing - dimensions.y > 0)
        {
            SDL_Rect elementBounds = {dimensions.x, listPos + elementSpacing, dimensions.w, originalSpacing};
            if (x >= elementBounds.x && x <= elementBounds.x + elementBounds.w &&
                y >= elementBounds.y && y <= elementBounds.y + elementBounds.h)
            {
                color = hoverColor;
                lastHoveredItem = i;
            }
            renderer.renderFont(font, (std::to_string(i + 1) + "- " + data[i]).c_str(), color, dimensions.x + margin, listPos + elementSpacing);
        }
        elementSpacing += 40;
        if (listPos + elementSpacing - 100 > dimensions.h)
            break;
    }
    elementSpacing = 0;
}

int ListBox::getLastHoveredItem() {
    return lastHoveredItem;
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

void ListBox::pushItem(std::string item)
{
    data.push_back(item);
    updateParams();
}

void ListBox::removeItem(int idx)
{
    data.erase(data.begin() + idx);
    updateParams();
}