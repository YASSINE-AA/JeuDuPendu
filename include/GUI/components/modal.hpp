#ifndef MODAL_HPP
#define MODAL_HPP

#include "customComponent.hpp"
#include "textBox.hpp"
#include <vector>

class Modal : public CustomComponent
{
public:
    Modal(Renderer &renderer, States &states, Window &window, TTF_Font *&font, TTF_Font *&contentFont, std::string title, std::string content)
        : CustomComponent(renderer, states), window(window), font(font), contentFont(contentFont), title(title), content(content), textBox(renderer, states, font, "", "ex: excellent", -1, -1)
    {
        x = width / 2 - modalW / 2;
        y = height / 2 - modalH / 2;
        std::tie(width, height) = window.getWindowDimensions();
        deleteBtnRect = (SDL_Rect){x + 30, y + 120, 55, 25};
        addBtnRect = (SDL_Rect){x + 30, y + 150, 55, 25};
    }
    int x, y;
    void render() override;
    void setTitle();
    void setContent();
    void setPosition(int x, int y) override {} // fix this
    void handleEvents(SDL_Event e) override;

private:
    int width, height;
    TextBox textBox;
    Window window;
    TTF_Font *font;
    TTF_Font *contentFont;
    SDL_Rect deleteBtnRect;
    SDL_Rect addBtnRect;
    int modalW = 300;
    int modalH = 250;
    int contentYOffset = 0;
    int contentXOffset = 0;
    std::string title;
    std::string content;
};

#endif
