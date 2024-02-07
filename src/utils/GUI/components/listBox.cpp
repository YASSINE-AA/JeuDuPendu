#include "listBox.hpp"

void ListBox::render()
{

    SDL_Color normalColor = {0, 0, 0};
    SDL_Color color = normalColor;
    SDL_Color hoverColor = {255, 0, 0};

    int x, y, addPos;
    states.getMousePosition(&x, &y);
    renderer.renderRectFilled(dimensions, {0, 0, 0}, {255, 255, 255});
    addPos = 45;
    renderer.renderRectFilled(addButtonDimensions, {0, 0, 0}, {255, 255, 255});
    for (size_t i = 0; i < wordCount; ++i)
    {
        color = normalColor;
        if (listPos + elementSpacing - dimensions.y > 0)
        {
            SDL_Rect elementBounds = {dimensions.x, listPos + elementSpacing + addPos, dimensions.w, originalSpacing};
            if (x >= elementBounds.x && x <= elementBounds.x + elementBounds.w &&
                y >= elementBounds.y && y <= elementBounds.y + elementBounds.h)
            {
                color = hoverColor;
                lastHoveredItem = i;
            }
            renderer.renderFont(font, (std::to_string(i + 1) + "- " + data[i]).c_str(), color, dimensions.x + margin, listPos + elementSpacing + addPos);
        }
        elementSpacing += 40;
        if (listPos + elementSpacing - 100 > dimensions.h)
            break;
    }
    renderer.renderFont(font, "Add a word", color, addButtonDimensions.x + margin, addButtonDimensions.y + margin);
    deleteModal.render();
    addModal.render();
    elementSpacing = 0;
}

int ListBox::getLastHoveredItem()
{
    return lastHoveredItem;
}

void ListBox::handleEvents(SDL_Event e)
{

    if (e.type == SDL_MOUSEWHEEL && !blockEvents)
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
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {

        int mouseX, mouseY;
        states.getMousePosition(&mouseX, &mouseY);

        if (deleteModal.isClosed() && states.isBtnArea(mouseX, mouseY, dimensions) && !states.isBtnArea(mouseX, mouseY, addButtonDimensions))
        {
            indexToDelete = getLastHoveredItem();
            deleteModal.setWord(data[indexToDelete]);
            deleteModal.setContent("Are you sure you want to delete: " + data[indexToDelete]);
            deleteModal.setVisibilty(true);
        }
        else
        {
            if (deleteModal.getSubmit())
            {
                std::string word = data[indexToDelete];
                // delete from tree
                tree.deleteWord(word);
                // delete from listbox
                removeItem(indexToDelete);
                // delete from dictionary
                dictionary.deleteFromFile("dict.txt", word);
                deleteModal.setVisibilty(false);
                deleteModal.resetSubmit();
            }
        }

        if (addModal.isClosed() && states.isBtnArea(mouseX, mouseY, addButtonDimensions))
        {
            indexToDelete = getLastHoveredItem();
            addModal.setWord(data[indexToDelete]);
            addModal.setTitle("Add a word!");
            addModal.setContent("Add a word");
            addModal.setVisibilty(true);
        }
        else
        {
            if (addModal.getSubmit())
            {
                std::string word = data[indexToDelete];
                // delete from tree
                tree.deleteWord(word);
                // delete from listbox
                removeItem(indexToDelete);
                // delete from dictionary
                dictionary.deleteFromFile("dict.txt", word);
                addModal.setVisibilty(false);
                addModal.resetSubmit();
            }
        }

        addModal.handleEvents(e);
        deleteModal.handleEvents(e);
    }
}

void ListBox::updateParams()
{
    std::cout << "updateParams called" << std::endl;
    wordCount = data.size();
    std::cout << wordCount << std::endl;
    listSize = wordCount * originalSpacing;
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