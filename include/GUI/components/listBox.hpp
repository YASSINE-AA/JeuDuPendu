#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "customComponent.hpp"

#include "deleteModal.hpp"
#include "addModal.hpp"

class ListBox : public CustomComponent
{
public:
    ListBox(Renderer &renderer, States &states, Window &window, TTF_Font *font, TTF_Font *contentFont, Dictionary dictionary, BinaryTree tree, SDL_Rect &dimensions, int elementSpacing)
        : CustomComponent(renderer, states), window(window), data(dictionary.allWords), dictionary(dictionary), font(font), dimensions(dimensions), elementSpacing(elementSpacing), tree(tree), addModal(AddModal(renderer, states, window, font, contentFont, "Do you want to delete", "test", tree, dictionary)), deleteModal(DeleteModal(renderer, states, window, font, contentFont, "Do you want to delete", "test", tree, dictionary))
    {
        listPos = dimensions.y + margin;
        wordCount = data.size();
        listSize = wordCount * elementSpacing;
        originalSpacing = elementSpacing;
        addButtonDimensions = (SDL_Rect){dimensions.x, dimensions.y, dimensions.w, addPos};
    }

    void render() override;
    void pushItem(std::string);
    int getLastHoveredItem();
    void removeItem(int idx);
    void listAllItems()
    {
        for (const std::string &word : data)
        {
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
    DeleteModal deleteModal;
    AddModal addModal;
    Dictionary dictionary;
    int indexToDelete;
    std::vector<std::string> data;
    Window window;
    int originalSpacing;
    BinaryTree tree;
    int listSize;
    int listPos;
    int wordCount;
    bool blockEvents = false;
    int lastHoveredItem;
    int margin = 10;
    int addPos = 45;
    TTF_Font *font;
    SDL_Rect dimensions;
    SDL_Rect addButtonDimensions;
    bool renderDeleteModal = false;

    int elementSpacing;
};

#endif
