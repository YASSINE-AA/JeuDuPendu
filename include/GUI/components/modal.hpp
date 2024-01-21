#ifndef MODAL_HPP
#define MODAL_HPP

#include "customComponent.hpp"
#include "textBox.hpp"
#include <vector>
#include "listBox.hpp"

class Modal : public CustomComponent
{
public:
    Modal(Renderer &renderer, States &states, Window &window, TTF_Font *&font, TTF_Font *&contentFont, std::string title, std::string content, ListBox &listbox)
        : CustomComponent(renderer, states), window(window), font(font), contentFont(contentFont), title(title), content(content), textBox(renderer, states, font, "", "ex: excellent", -1, -1), listBox(listbox)
    {
        listBox.pushItem("what");
        std::tie(width, height) = window.getWindowDimensions();
        x = width / 2 - modalW / 2;
        y = height / 2 - modalH / 2;
        addBtnRect = (SDL_Rect){x + 15, y + 140, 75, 33};
        deleteBtnRect = (SDL_Rect){x + 100, y + 140, 75, 33};
    }

    int x, y;
    void render() override;
    void setTitle();
    void setContent();
    void setPosition(int x, int y) override {} // fix this
    void pushItemToListBox(std::string &item) {
        listBox.pushItem(item);
    }
    void handleEvents(SDL_Event e) override;

private:
    int width, height;
    TextBox textBox;
    ListBox listBox;
    Window window;
    TTF_Font *font;
    TTF_Font *contentFont;
    SDL_Rect deleteBtnRect;
    SDL_Rect addBtnRect;
    int modalW = 300;
    int modalH = 200;
    int contentYOffset = 0;
    int contentXOffset = 0;
    std::string title;
    std::string content;
};

#endif
